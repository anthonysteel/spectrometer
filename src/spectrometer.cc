#include "spectrometer.h"

Spectrometer::
Spectrometer(std::vector<spec_config_param> config_vector)
    :SpecConfigValidator("/home/pi/spectrometer/config/meas_config.csv")
{

    for(const spec_config_param& param : config_vector) {
        try {
            if (SpecConfigValidator.validate(param)) {
                MeasConfigTypeBuilder meas_config_type_builder;
                spec_config = meas_config_type_builder.build(config_vector);
            } else {
                throw std::range_error(param.name + " with value "
                                       + param.value
                                       + " is out of range");
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void
Spectrometer::
activate()
{
    AvsIdentityType device_id_info[30];
    int USB_port = 0;
    int init_return = AVS_Init(USB_port);
    if (init_return < 0) {
        throw std::runtime_error("AVS_Init failed with: "
                                 + SpecException.lookup(init_return));
    } else if (init_return == 0) {
        throw std::runtime_error("AVS_Init failed with: NO_DEVICE_FOUND");
    }


    int update_usb_return = AVS_UpdateUSBDevices();
    if (update_usb_return < 0) {
        throw std::runtime_error("AVS_UpdateUSBDevices failed with: "
                                 + SpecException.lookup(update_usb_return));
    } else if (update_usb_return == 0) {
        throw std::runtime_error("AVS_UpdateUSBDevices failed with: NO_DEVICE_FOUND");
    }

    unsigned int required_bytes;

    int getlist_return = AVS_GetList(sizeof(device_id_info),
                                     &required_bytes, device_id_info);
    if (getlist_return < 0) {
        throw std::runtime_error("AVS_GetList failed with: "
                                 + SpecException.lookup(getlist_return));
    } else if (getlist_return == 0) {
        throw std::runtime_error("AVS_GetList failed with: NO_DEVICE_FOUND");
    }


    int activate_return = AVS_Activate( &device_id_info[0] );
    if (activate_return >= 0) {
        device_id = activate_return;
    } else {
        throw std::runtime_error("AVS_Activate failed with: "
                                 + SpecException.lookup(activate_return));
    }

    int prepare_measure_return = AVS_PrepareMeasure(device_id, &spec_config);
    if (prepare_measure_return >= 0) {
        throw std::runtime_error("AVS_PrepareMeasure failed with: "
                                 + SpecException.lookup(prepare_measure_return));
    }
}

void
Spectrometer::
deactivate()
{
    bool deactivate_return = AVS_Deactivate(device_id);
    if (deactivate_return != true) {
        throw std::runtime_error("Spectrometer failed to deactivate, device id incorrect");
    }
}


std::vector<double>
Spectrometer::
measure()
{
    int measurecallback_return = AVS_MeasureCallback( device_id, NULL, 1 );

    int msmt_sts;

    if (measurecallback_return == 0) {
        msmt_sts = measurecallback_return;
    } else {
        throw std::runtime_error("AVS_MeasureCallback failed with: "
                                 + SpecException.lookup(measurecallback_return));
    }

    unsigned int required_delay = 10; // ms

    int attempts = 0;
    int pollscan_return;
    while(!(pollscan_return = AVS_PollScan(device_id)) && attempts != 100) {
        if (pollscan_return == 0) {
            usleep(required_delay);
            attempts++;
        } else {
            throw std::runtime_error("AVS_PollScan failed with: "
                                     + SpecException.lookup(pollscan_return));
        }
    }

    std::vector<double> spec_measurement_data;

    double *data_buffer = new double[2048];
    unsigned int *time_label = new unsigned int[100];

    int get_data_return;
    for(int i = 0; i < 2048; i++) {
        get_data_return = AVS_GetScopeData(device_id, time_label, data_buffer);
        if (get_data_return == 0) {
            spec_measurement_data.push_back(data_buffer[i]);
        } else {
            throw std::runtime_error("AVS_GetScopeData threw : "
                                     + SpecException.lookup(get_data_return));
        }
    }

    delete[] data_buffer;
    delete[] time_label;

    return spec_measurement_data;
}


float
Spectrometer::
voltageToCelsius(float analog_reading)
{
    return 118.69
           - 70.361 * analog_reading
           + 21.02 * pow(analog_reading, 2.0)
           - 3.6443 * pow(analog_reading, 3.0)
           + 0.1993 * pow(analog_reading, 4.0);
}

float
Spectrometer::
getThermistor()
{
    float *analog_reading = new float;
    int analog_in_return = AVS_GetAnalogIn(device_id, 0, analog_reading);
    if (analog_in_return == 0) {
        float temperature_reading = voltageToCelsius(*analog_reading);
        delete analog_reading;
        return temperature_reading;
    } else {
        delete analog_reading;
        throw std::runtime_error("AVS_GetAnalogIn failed with: "
                                 + SpecException.lookup(analog_in_return));
    }
}

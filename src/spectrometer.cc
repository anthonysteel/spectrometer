#include "spectrometer.h"

Spectrometer::
Spectrometer(std::vector<spec_config_param> config_vector)
    :SpecConfigValidator("/home/pi/spectrometer/config/meas_config.csv"), avs()
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
    int usb_port = 0;
    avs.Init(usb_port);

    int device_number = 0;
    device_id = avs.Activate(device_number);

    avs.PrepareMeasure(device_id, &spec_config);
}

void
Spectrometer::
deactivate()
{
    avs.Deactivate(device_id);
}


std::vector<double>
Spectrometer::
measure()
{
    avs.Measure( device_id, 1 );

    int required_delay = 10; // ms
    int attempts = 0;
    int pollscan_return;

    while(!(pollscan_return = avs.PollScan(device_id)) && attempts != 100) {
        usleep(required_delay);
        attempts++;
    }

    std::vector<double> spec_measurement_data;

    double *data_buffer = new double[2048];
    unsigned int *time_label = new unsigned int[100];

    int get_data_return;
    for(int i = 0; i < 2048; i++) {
        avs.GetScopeData(device_id, time_label, data_buffer);
        spec_measurement_data.push_back(data_buffer[i]);
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

    avs.GetAnalogIn(device_id, 0, analog_reading);
    float temperature_reading = voltageToCelsius(*analog_reading);

    delete analog_reading;

    return temperature_reading;
}

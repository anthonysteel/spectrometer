#include <unistd.h>
#include <string>
#include "spectrometer.h"
#include "validator.h"
#include "meas_config_type_builder.h"

Spectrometer::Spectrometer(std::vector<spec_config_param> config_vector)
{
    SpecConfigValidator;

    for(const spec_config_param& param : config_vector)
    {
        std::cout << param.name << " " << param.value << " " 
        << SpecConfigValidator.validate(param) << std::endl;
        if (SpecConfigValidator.validate(param))
        {
            MeasConfigTypeBuilder meas_config_type_builder;

            spec_config = meas_config_type_builder.build(config_vector);
        }
        else
        {
            std::cout << "Param didn't validate" << std::endl;
        }
    }
}

void Spectrometer::activate()
{
	AvsIdentityType device_id_info[30];

	int USB_port = 0; 
    std::cout << std::endl;
    std::cout << "AVS_Init(): " << AVS_Init(USB_port) << std::endl; 

    std::cout << "Number of USB device: " << AVS_UpdateUSBDevices() << std::endl;
	
	unsigned int required_bytes;
	AVS_GetList(sizeof(device_id_info), &required_bytes, device_id_info);

	device_id = AVS_Activate( &device_id_info[0] );

    std::cout << "AVS_PrepareMeasure(): " << AVS_PrepareMeasure(device_id, &spec_config) << std::endl;
}

std::vector<double> Spectrometer::measure()
{
	int msmt_sts = AVS_MeasureCallback( device_id, NULL, 1 );
	
    unsigned int required_delay = 10; // ms

    std::cout << "Device id: " << device_id << std::endl;

	while( !AVS_PollScan(device_id) )
	{
        usleep(required_delay);
	}
    std::cout << "hello" << std::endl;

    std::vector<double> spec_measurement_data;

    double *data_buffer = new double[2048];
    unsigned int *time_label = new unsigned int[100];

	for(int i = 0; i < 2048; i++)
	{
	   AVS_GetScopeData(device_id, time_label, data_buffer);
       std::cout << "at " << i << " the value is " << data_buffer[i] << std::endl;
       spec_measurement_data.push_back(data_buffer[i]);
	}

    return spec_measurement_data;
}

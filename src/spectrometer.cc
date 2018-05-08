#include <unistd.h>
#include <string>
#include "spectrometer.h"
#include "validator.h"
#include "meas_config_type_builder.h"

Spectrometer::
Spectrometer(std::vector<spec_config_param> config_vector)
{
    SpecConfigValidator;

    for(const spec_config_param& param : config_vector)
    {
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

void 
Spectrometer::
activate()
{
	AvsIdentityType device_id_info[30];

	int USB_port = 0; 

    AVS_Init(USB_port); 

    AVS_UpdateUSBDevices();
	
	unsigned int required_bytes;
	AVS_GetList(sizeof(device_id_info), &required_bytes, device_id_info);

	device_id = AVS_Activate( &device_id_info[0] );

    AVS_PrepareMeasure(device_id, &spec_config);
}

std::vector<double> 
Spectrometer::
measure()
{
	int msmt_sts = AVS_MeasureCallback( device_id, NULL, 1 );
	
    unsigned int required_delay = 10; // ms

	while( !AVS_PollScan(device_id) )
	{
        usleep(required_delay);
	}

    std::vector<double> spec_measurement_data;

    double *data_buffer = new double[2048];
    unsigned int *time_label = new unsigned int[100];

	for(int i = 0; i < 2048; i++)
	{
	   AVS_GetScopeData(device_id, time_label, data_buffer);
       spec_measurement_data.push_back(data_buffer[i]);
	}

    delete[] data_buffer;
    delete[] time_label;

    return spec_measurement_data;
}

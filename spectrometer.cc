#include "spectrometer.h"

void
Spectrometer::defineConfigLookup()
{
    UINT32_config_lookup["integration_delay"] = &spec_config
                                                .m_IntegrationDelay;
    UINT32_config_lookup["number_averages"] = &spec_config.m_NrAverages;
    UINT32_config_lookup["laser_delay"] = &spec_config.m_Control.m_LaserDelay;
    UINT32_config_lookup["laser_width"] = &spec_config.m_Control.m_LaserWidth;
    UINT16_config_lookup["smooth_pixel"] = &spec_config.m_Smoothing
                                                .m_SmoothPix;
    UINT16_config_lookup["strobe_control"] = &spec_config.m_Control
                                                         .m_StrobeControl;
    UINT16_config_lookup["start_pixel"] = &spec_config.m_StartPixel;
    UINT16_config_lookup["stop_pixel"] = &spec_config.m_StopPixel;
    UINT8_config_lookup["enable"] = &spec_config.m_CorDynDark.m_Enable;
    UINT8_config_lookup["forget_percentage"] = &spec_config.m_CorDynDark
                                              .m_ForgetPercentage;
    UINT8_config_lookup["smooth_model"] = &spec_config.m_Smoothing
                                         .m_SmoothModel;
    UINT8_config_lookup["mode"] = &spec_config.m_Trigger.m_Mode;
    UINT8_config_lookup["source"] = &spec_config.m_Trigger.m_Source;
    UINT8_config_lookup["source_type"] = &spec_config.m_Trigger.m_SourceType;
    FLOAT_config_lookup["laser_wavelength"] = &spec_config.m_Control
                                                .m_LaserWaveLength;
    FLOAT_config_lookup["integration_time"] = &spec_config.m_IntegrationTime;
}

void
Spectrometer::assignMeasConfigType(struct spec_config_param param)
{
    if(param.type == "uint32")
    {
        *UINT32_config_lookup[param.name] = 
        ::stringToNumber<uint32>(param.value);
    }
    else if(param.type == "uint16")
    {
        *UINT16_config_lookup[param.name] = 
        ::stringToNumber<uint16>(param.value);
    }
    else if(param.type == "uint8")
    {
        *UINT8_config_lookup[param.name] =
        ::stringToNumber<uint8>(param.value);
    }
    else if(param.type == "float")
    {
        *FLOAT_config_lookup[param.name] = 
        ::stringToNumber<float>(param.value);
    }
}


Spectrometer::Spectrometer(
    const std::vector<struct spec_config_param>& config_vector,
    const std::shared_ptr<AvaSpecConnection>& avaspec)
: UINT32_validator("uint32")
, UINT16_validator("uint16")
, UINT8_validator("uint8")
, FLOAT_validator("float")
, connector_(avaspec)
{
    /**
    for(const struct spec_config_param& param : config_vector)
    {
        if((param.type == "uint32" && UINT32_validator.validate(param))
           || (param.type == "uint16" && UINT16_validator.validate(param))
           || (param.type == "uint8" && UINT8_validator.validate(param))
           || (param.type == "float" && FLOAT_validator.validate(param)))
        {
            assignMeasConfigType(param);
        }
    }
    //setAvaSpecParameters(spec_config); 
    */
}

void Spectrometer::activate()
{
	AvsIdentityType device_id_info[30];

	int USB_port = 1; 
	connector_->Init(USB_port);

	/*
	AVS_UpdateUSBDevices();
	
	unsigned int required_bytes;
	AVS_GetList(sizeof(device_id_info), &required_bytes, device_id_info);

	device_id = AVS_Activate( &device_id_info[0] );
	*/
}

std::vector<double> Spectrometer::measure()
{
	int msmt_sts = AVS_MeasureCallback( device_id, NULL, 1 );
	
    unsigned int required_delay = 10; // ms
	while( !AVS_PollScan(device_id) )
	{
        usleep(required_delay);
	}

    std::vector<double> spec_measurement_data;

    double *data_buffer = new double[2047];
    unsigned int *time_label = new unsigned int[100];

	for(int i = 0; i < 2047; i++)
	{
	   AVS_GetScopeData(device_id, time_label, data_buffer);
       spec_measurement_data.push_back(data_buffer[i]);
	}

    delete[] data_buffer;
    delete[] time_label;

    return spec_measurement_data;
}

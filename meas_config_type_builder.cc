#include "meas_config_type_builder.h"

MeasConfigTypeBuilder::
MeasConfigTypeBuilder()

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
    UINT16_config_lookup["store_to_ram"] = &spec_config.m_Control
                                                       .m_StoreToRam;
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

MeasConfigType
MeasConfigTypeBuilder::
build(std::vector<spec_config_param> config_vector)
{
    for (auto const& param : config_vector)
    {
        if(UINT32_config_lookup[param.name])
        {
            *UINT32_config_lookup[param.name] = 
            stringToNumber<uint32>(param.value);
        }
        else if(UINT16_config_lookup[param.name])
        {
            *UINT16_config_lookup[param.name] = 
            stringToNumber<uint16>(param.value);
        }
        else if(UINT8_config_lookup[param.name])
        {
            *UINT8_config_lookup[param.name] =
            stringToNumber<uint8>(param.value);
        }
        else if(FLOAT_config_lookup[param.name])
        {
            *FLOAT_config_lookup[param.name] = 
            stringToNumber<float>(param.value);
        }
        else
        {
            std::cout << 
            "The param type did not match one of the config types" <<
            std::endl;
        }
    }

    return spec_config;
}

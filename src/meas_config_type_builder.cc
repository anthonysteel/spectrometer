#include "meas_config_type_builder.h"

MeasConfigType
MeasConfigTypeBuilder::
build(std::vector<spec_config_param> config_vector)
{
    for (auto const& param : config_vector)
    {
        if (param.name == "integration_delay")  
        {
            spec_config.m_IntegrationDelay = stringToNumber<uint32>(param.value);
        }
        else if (param.name == "number_averages")
        {
            spec_config.m_NrAverages = stringToNumber<uint32>(param.value);
        }
        else if (param.name == "laser_delay")
        {
            spec_config.m_Control.m_LaserDelay = stringToNumber<uint32>(param.value);
        }
        else if (param.name == "laser_width")
        {
            spec_config.m_Control.m_LaserWidth = stringToNumber<uint32>(param.value);
        }
        else if (param.name == "smooth_pixel")
        {
            spec_config.m_Smoothing.m_SmoothPix = stringToNumber<uint16>(param.value);
        }
        else if (param.name == "strobe_control")
        {
            spec_config.m_Control.m_StrobeControl = stringToNumber<uint16>(param.value);
        }
        else if (param.name == "start_pixel")
        {
            spec_config.m_StartPixel = stringToNumber<uint16>(param.value);
        }
        else if (param.name == "stop_pixel")
        {
            spec_config.m_StopPixel = stringToNumber<uint16>(param.value);
        }
        else if (param.name == "store_to_ram")
        {
            spec_config.m_Control.m_StoreToRam = stringToNumber<uint16>(param.value);
        }
        else if (param.name == "enable")
        {
            spec_config.m_CorDynDark.m_Enable = stringToNumber<uint8>(param.value);
        }
        else if (param.name == "forget_percentage")
        {
            spec_config.m_CorDynDark.m_ForgetPercentage = stringToNumber<uint8>(param.value);
        }
        else if (param.name == "smooth_model")
        {
            spec_config.m_Smoothing.m_SmoothModel = stringToNumber<uint8>(param.value);
        }
        else if (param.name == "mode")
        {
            spec_config.m_Trigger.m_Mode = stringToNumber<uint8>(param.value);
        }
        else if (param.name == "source")
        {
            spec_config.m_Trigger.m_Source = stringToNumber<uint8>(param.value);
        }
        else if (param.name == "source_type")
        {
            spec_config.m_Trigger.m_SourceType = stringToNumber<uint8>(param.value);
        }
        else if (param.name == "laser_wavelength")
        {
            spec_config.m_Control.m_LaserWaveLength = stringToNumber<float>(param.value);
        }
        else if (param.name == "integration_time")
        {
            spec_config.m_IntegrationTime = stringToNumber<float>(param.value);
        }
    }
    return spec_config;
}

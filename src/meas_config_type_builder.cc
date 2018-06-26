#include "meas_config_type_builder.h"
MeasConfigType MeasConfigTypeBuilder::build(
        std::vector<spec_config_param> config_vector)
{
    for (auto const& param : config_vector)
    {
        if (param.name == "integration_delay")  {
            spec_config.m_IntegrationDelay = param.value;
        } else if (param.name == "number_averages") {
            spec_config.m_NrAverages = param.value;
        } else if (param.name == "laser_delay") {
            spec_config.m_Control.m_LaserDelay = param.value;
        } else if (param.name == "laser_width") {
            spec_config.m_Control.m_LaserWidth = param.value;
        } else if (param.name == "smooth_pixel") {
            spec_config.m_Smoothing.m_SmoothPix = param.value;//uint16
        } else if (param.name == "strobe_control") {
            spec_config.m_Control.m_StrobeControl = param.value;//uint16
        } else if (param.name == "start_pixel") {
            spec_config.m_StartPixel = param.value;//uint16
        } else if (param.name == "stop_pixel") {
            spec_config.m_StopPixel = param.value;//uint16
        } else if (param.name == "store_to_ram") {
            spec_config.m_Control.m_StoreToRam = param.value;//uint16
        } else if (param.name == "enable") {
            spec_config.m_CorDynDark.m_Enable = param.value;//uint8
        } else if (param.name == "forget_percentage") {
            spec_config.m_CorDynDark.m_ForgetPercentage = param.value;//uint8
        } else if (param.name == "smooth_model") {
            spec_config.m_Smoothing.m_SmoothModel = param.value;//uint8
        } else if (param.name == "mode") {
            spec_config.m_Trigger.m_Mode = param.value;//uint8
        } else if (param.name == "source") {
            spec_config.m_Trigger.m_Source = param.value;//uint8
        } else if (param.name == "source_type") {
            spec_config.m_Trigger.m_SourceType = param.value;//uint8
        } else if (param.name == "laser_wavelength") {
            spec_config.m_Control.m_LaserWaveLength = param.value;//float
        } else if (param.name == "integration_time") {
            spec_config.m_IntegrationTime = param.value;//float
        }
    }
    return spec_config;
}

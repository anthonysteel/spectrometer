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

/*
int main()
{

    std::vector<spec_config_param> config_vector;
    config_vector = {
        {"laser_wavelength", "785"},
        {"start_pixel", "0"},
        {"stop_pixel", "2047"},
        {"integration_time", "100"},
        {"integration_delay", "1"},
        {"number_averages", "1"},
        {"enable", "0"},
        {"forget_percentage", "100"},
        {"smooth_pixel", "0"},
        {"smooth_model", "0"},
        {"mode", "0"},
        {"source", "0"},
        {"source_type", "1"},
        {"strobe_control", "0"},
        {"laser_delay", "0"},
        {"laser_width", "10000"},
        {"store_to_ram", "5"}
    };    

    MeasConfigTypeBuilder meas_config_type_builder;

    MeasConfigType* spec_config = meas_config_type_builder.build(config_vector);

    std::cout <<
        "start pixel: " <<
        spec_config->m_StartPixel <<
    std::endl;

    std::cout <<
        "stop pixel: " <<
        spec_config->m_StopPixel <<
    std::endl;

    std::cout <<
        "integration time: " <<
        spec_config->m_IntegrationTime <<
    std::endl;

    std::cout << 
        "integration delay: " << 
        spec_config->m_IntegrationDelay <<
    std::endl;

    std::cout << 
        "nraverages: " <<
        spec_config->m_NrAverages <<
    std::endl;

    std::cout << 
        "enable: " <<
        +spec_config->m_CorDynDark.m_Enable <<
    std::endl;

    std::cout << 
        "forget percentage: " <<
        +spec_config->m_CorDynDark.m_ForgetPercentage <<
    std::endl; 

    std::cout <<
        "smooth pixel: " <<
        spec_config->m_Smoothing.m_SmoothPix <<
    std::endl;

    std::cout <<
        "smooth model: " <<
        +spec_config->m_Smoothing.m_SmoothModel <<
    std::endl;

    std::cout <<
        "mode: " <<
        +spec_config->m_Trigger.m_Mode <<
    std::endl;

    std::cout <<
        "source: " <<
        +spec_config->m_Trigger.m_Source <<
    std::endl;

    std::cout <<
        "source type: " <<
        +spec_config->m_Trigger.m_SourceType <<
    std::endl;

    std::cout <<
        "strobe control: " <<
        spec_config->m_Control.m_StrobeControl <<
    std::endl;

    std::cout << 
        "laser delay: " <<
        spec_config->m_Control.m_LaserDelay <<
    std::endl;

    std::cout << 
        "laser width: " <<
        spec_config->m_Control.m_LaserWidth <<
    std::endl;

    std::cout <<
        "laser wavelength: " <<
        spec_config->m_Control.m_LaserWaveLength <<
    std::endl;

    std::cout <<
        "laser wavelength: " <<
        spec_config->m_Control.m_StoreToRam <<
    std::endl;
}
*/

#include "gtest/gtest.h"
#include "meas_config_type_builder.h"

TEST(MeasConfigTypeBuilder, Build)
{
    MeasConfigTypeBuilder meas_config_type_builder;

    std::vector<spec_config_param> config_vector;
    config_vector = {
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
        {"laser_wavelength", "785"},
        {"store_to_ram", "5"}
    };    

    MeasConfigType spec_config = meas_config_type_builder.build(config_vector);

    std::cout <<
        "start pixel: " <<
        spec_config.m_StartPixel <<
    std::endl;

    std::cout <<
        "stop pixel: " <<
        spec_config.m_StopPixel <<
    std::endl;

    std::cout <<
        "integration time: " <<
        spec_config.m_IntegrationTime <<
    std::endl;

    std::cout << 
        "integration delay: " << 
        spec_config.m_IntegrationDelay <<
    std::endl;

    std::cout << 
        "nraverages: " <<
        spec_config.m_NrAverages <<
    std::endl;

    std::cout << 
        "enable: " <<
        +spec_config.m_CorDynDark.m_Enable <<
    std::endl;

    std::cout << 
        "forget percentage: " <<
        +spec_config.m_CorDynDark.m_ForgetPercentage <<
    std::endl; 

    std::cout <<
        "smooth pixel: " <<
        spec_config.m_Smoothing.m_SmoothPix <<
    std::endl;

    std::cout <<
        "smooth model: " <<
        +spec_config.m_Smoothing.m_SmoothModel <<
    std::endl;

    std::cout <<
        "mode: " <<
        +spec_config.m_Trigger.m_Mode <<
    std::endl;

    std::cout <<
        "source: " <<
        +spec_config.m_Trigger.m_Source <<
    std::endl;

    std::cout <<
        "source type: " <<
        +spec_config.m_Trigger.m_SourceType <<
    std::endl;

    std::cout <<
        "strobe control: " <<
        spec_config.m_Control.m_StrobeControl <<
    std::endl;

    std::cout << 
        "laser delay: " <<
        spec_config.m_Control.m_LaserDelay <<
    std::endl;

    std::cout << 
        "laser width: " <<
        spec_config.m_Control.m_LaserWidth <<
    std::endl;

    std::cout <<
        "laser wavelength: " <<
        spec_config.m_Control.m_LaserWaveLength <<
    std::endl;

    std::cout <<
        "laser wavelength: " <<
        spec_config.m_Control.m_StoreToRam <<
    std::endl;

    EXPECT_EQ(spec_config.m_StartPixel, 1);
    EXPECT_EQ(spec_config.m_StopPixel, 2047);
    EXPECT_EQ(spec_config.m_IntegrationTime, 100);
    EXPECT_EQ(spec_config.m_IntegrationDelay, 1);
    EXPECT_EQ(spec_config.m_NrAverages, 1);
    EXPECT_EQ(spec_config.m_CorDynDark.m_enable, 0);
    EXPECT_EQ(spec_config.m_CorDynDark.m_forgetpercentage, 100);
    EXPECT_EQ(spec_config.m_Smoothing.m_SmoothPix, 0);
    EXPECT_EQ(spec_config.m_Smoothing.m_SmoothModel, 0);
    EXPECT_EQ(spec_config.m_Trigger.m_Mode, 0);
    EXPECT_EQ(spec_config.m_Trigger.m_Source, 0);
    EXPECT_EQ(spec_config.m_Trigger.m_SourceType, 1);
    EXPECT_EQ(spec_config.m_Control.m_StrobeControl, 0);
    EXPECT_EQ(spec_config.m_Control.m_LaserDelay, 0);
    EXPECT_EQ(spec_config.m_Control.m_LaserWidth, 10000);
    EXPECT_EQ(spec_config.m_Control.m_LaserWaveLength, 1);
    EXPECT_EQ(spec_config.m_Control.m_StoreToRam, 5);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/* vim: set ts=4 sw=4 et :*/

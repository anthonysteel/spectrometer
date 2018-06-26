#include "gtest/gtest.h"
#include "meas_config_type_builder.h"


TEST(MeasConfigTypeBuilder, StartPixel)
{
MeasConfigTypeBuilder meas_config_type_builder;
std::vector<spec_config_param> config_vector = {
    {"start_pixel", 0},
    {"stop_pixel", 2047},
    {"integration_time", 100},
    {"integration_delay", 1},
    {"number_averages", 1},
    {"enable", "0"},
    {"forget_percentage", 100},
    {"smooth_pixel", 0},
    {"smooth_model", 0},
    {"mode", 0},
    {"source", 0},
    {"source_type", 1},
    {"strobe_control", 0},
    {"laser_delay", 0},
    {"laser_width", 10000},
    {"laser_wavelength", 785},
    {"store_to_ram", 5}
};    
MeasConfigType spec_config = meas_config_type_builder.build(config_vector);
    EXPECT_EQ(spec_config.m_StartPixel, 0);
}

TEST(MeasConfigTypeBuilder, StopPixel)
{
    EXPECT_EQ(spec_config.m_StopPixel, 2047);
}

TEST(MeasConfigTypeBuilder, IntegrationTime)
{
    EXPECT_EQ(spec_config.m_IntegrationTime, 100);
}

TEST(MeasConfigTypeBuilder, IntegrationDelay)
{
    EXPECT_EQ(spec_config.m_IntegrationDelay, 1);
}

TEST(MeasConfigTypeBuilder, NrAverages)
{
    EXPECT_EQ(spec_config.m_NrAverages, 1);
}

TEST(MeasConfigTypeBuilder, Enable)
{
    EXPECT_EQ(spec_config.m_CorDynDark.m_Enable, 0);
}

TEST(MeasConfigTypeBuilder, ForgetPercentage)
{
    EXPECT_EQ(spec_config.m_CorDynDark.m_ForgetPercentage, 100);
}

TEST(MeasConfigTypeBuilder, SmoothPix)
{
    EXPECT_EQ(spec_config.m_Smoothing.m_SmoothPix, 0);
}

TEST(MeasConfigTypeBuilder, SmoothModel)
{
    EXPECT_EQ(spec_config.m_Smoothing.m_SmoothModel, 0);
}

TEST(MeasConfigTypeBuilder, Mode)
{
    EXPECT_EQ(spec_config.m_Trigger.m_Mode, 0);
}

TEST(MeasConfigTypeBuilder, Source)
{
    EXPECT_EQ(spec_config.m_Trigger.m_Source, 0);
}

TEST(MeasConfigTypeBuilder, SourceType)
{
    EXPECT_EQ(spec_config.m_Trigger.m_SourceType, 1);
}

TEST(MeasConfigTypeBuilder, StrobeControl)
{
    EXPECT_EQ(spec_config.m_Control.m_StrobeControl, 0);
}

TEST(MeasConfigTypeBuilder, LaserDelay)
{
    EXPECT_EQ(spec_config.m_Control.m_LaserDelay, 0);
}

TEST(MeasConfigTypeBuilder, LaserWidth)
{
    EXPECT_EQ(spec_config.m_Control.m_LaserWidth, 10000);
}

TEST(MeasConfigTypeBuilder, LaserWaveLength)
{
    EXPECT_EQ(spec_config.m_Control.m_LaserWaveLength, 785);
}

TEST(MeasConfigTypeBuilder, StoreToRam)
{
    EXPECT_EQ(spec_config.m_Control.m_StoreToRam, 5);
}


int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/* vim: set ts=4 sw=4 et :*/

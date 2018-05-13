#include "gtest/gtest.h"
#include "spectrometer.h"
#include "spectrometer_structures.h"
#include <vector>
#include "type.h"

TEST(Spectrometer, measure)
{
    std::vector<spec_config_param> config_vector;
    config_vector = {
        {"start_pixel", "0"},
        {"stop_pixel", "2047"},
        {"integration_time", "100"},
        {"integration_delay", "0"},
        {"number_averages", "1"},
        {"enable", "0"},
        {"forget_percentage", "100"},
        {"smooth_pixel", "0"},
        {"smooth_model", "0"},
        {"mode", "0"},
        {"source", "0"},
        {"source_type", "0"},
        {"strobe_control", "0"},
        {"laser_delay", "0"},
        {"laser_width", "10000"},
        {"laser_wavelength", "785"},
        {"store_to_ram", "1"}
    };    

    Spectrometer s(config_vector);
    s.activate();

    std::vector<double> data = s.measure();
}

TEST(Spectrometer, getThermistor)
{
    std::vector<spec_config_param> config_vector;
    config_vector = {
        {"start_pixel", "0"},
        {"stop_pixel", "2047"},
        {"integration_time", "100"},
        {"integration_delay", "0"},
        {"number_averages", "1"},
        {"enable", "0"},
        {"forget_percentage", "100"},
        {"smooth_pixel", "0"},
        {"smooth_model", "0"},
        {"mode", "0"},
        {"source", "0"},
        {"source_type", "0"},
        {"strobe_control", "0"},
        {"laser_delay", "0"},
        {"laser_width", "10000"},
        {"laser_wavelength", "785"},
        {"store_to_ram", "1"}
    };    

    Spectrometer s(config_vector);
    s.activate();
    float thermistor_value = s.getThermistor();
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/* vim: set ts=4 sw=4 et :*/

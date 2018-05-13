#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include "validator.h"

Validator spec_param_validator;

TEST(Validator, parseRow);
{
    std::string row;
    std::ifstream config_file;
    config_file.open("/home/pi/spectrometer/test/validator.csv");

    if (config_file.is_open())
    {
        while (std::getline(config_file, row))
        {
            spec_param_validator.parseRow(row);
        }
    }

    MeasConfigType spec_config = meas_config_type_builder.build(config_vector);

    std::cout <<
        "start pixel: " <<
        spec_config.m_StartPixel <<
    std::endl;
    
    EXPECT_EQ(spec_config.m_StartPixel, 1);
}

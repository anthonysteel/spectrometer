import sys
import os
from os import path
from string import Template

PATH_TO_TESTS = path.join(path.dirname(__file__), '../test')
OUTPUT_FILEPATH = path.join(PATH_TO_TESTS, 'meas_config_type_builder.test.cc')

config_vector = [
    {"start_pixel": "0"},
    {"stop_pixel": "2047"},
    {"integration_time": "100"},
    {"integration_delay": "1"},
    {"number_averages": "1"},
    {"enable": "0"},
    {"forget_percentage": "100"},
    {"smooth_pixel": "0"},
    {"smooth_model": "0"},
    {"mode": "0"},
    {"source": "0"},
    {"source_type": "1"},
    {"strobe_control": "0"},
    {"laser_delay": "0"},
    {"laser_width": "10000"},
    {"laser_wavelength": "785"},
    {"store_to_ram": "5"}
]

names = ['StartPixel', 'StopPixel', 'IntegrationTime',
         'IntegrationDelay', 'NrAverages', 'CorDynDark.m_Enable',
         'CorDynDark.m_ForgetPercentage', 'Smoothing.m_SmoothPix',
         'Smoothing.m_SmoothModel', 'Trigger.m_Mode', 'Trigger.m_Source',
         'Trigger.m_SourceType', 'Control.m_StrobeControl',
         'Control.m_LaserDelay', 'Control.m_LaserWidth',
         'Control.m_LaserWaveLength', 'Control.m_StoreToRam']

file_template = Template("""#include "gtest/gtest.h"
#include "meas_config_type_builder.h"

MeasConfigTypeBuilder meas_config_type_builder;

std::vector<spec_config_param> config_vector = {
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

${tests}
int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/* vim: set ts=4 sw=4 et :*/
""")


test_template = Template("""TEST(MeasConfigTypeBuilder, ${test_name})
{
    EXPECT_EQ(spec_config.m_${var_name}, ${val});
}

""")


def main():

    tests_string = ''
    for i, var_name in enumerate(names):
        test_name = var_name
        if 'm_' in test_name:
            test_name = test_name.split('m_')[1]
        val = list(config_vector[i].values())[0]
        tests_string += test_template.substitute(test_name=test_name,
                                                 var_name=var_name, val=val)

    with open(OUTPUT_FILEPATH, 'w') as f:
        f.write(file_template.substitute(tests=tests_string))


if __name__ == '__main__':
    main()

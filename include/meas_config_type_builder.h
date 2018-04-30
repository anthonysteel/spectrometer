#ifndef MEAS_CONFIG_TYPE_BUILDER_H
#define MEAS_CONFIG_TYPE_BUILDER_H

#include <unordered_map>
#include "avaspec.h"
#include <iostream>
#include <vector>
#include "spectrometer_structures.h"
#include "stringToNumber.h"

class MeasConfigTypeBuilder
{
    public:
        MeasConfigType spec_config;

        MeasConfigType build(std::vector<spec_config_param> config_vector);

    private:

        std::unordered_map<std::string, uint32*>
        UINT32_config_lookup;

        std::unordered_map<std::string, uint16*>
        UINT16_config_lookup;

        std::unordered_map<std::string, uint8*>
        UINT8_config_lookup;

        std::unordered_map<std::string, float*>
        FLOAT_config_lookup;
};

#endif

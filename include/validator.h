#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "parser.h"
#include "type.h"
#include "spectrometer_structures.h"
#include "stringToNumber.h"

class Validator
{
    public:
        Validator();

        bool
        validate(spec_config_param unvalidated_param);

    private:
        std::unordered_map<std::string, validator_map_entry>
        validator_lookup;

        template <class TYPE>
        bool
        validate_entry(spec_config_param unvalidated_param,
                       validator_map_entry entry);
};

template <class TYPE>
bool
Validator::
validate_entry(spec_config_param unvalidated_param, validator_map_entry entry)
{
    TYPE lower = stringToNumber<TYPE>(entry.lower);
    TYPE upper = stringToNumber<TYPE>(entry.upper);
    TYPE value = stringToNumber<TYPE>(unvalidated_param.value); 
    return value >= lower && value <= upper;
}

#endif

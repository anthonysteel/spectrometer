#ifndef SPECTROMETER_CONFIG_VALIDATOR
#define SPECTROMETER_CONFIG_VALIDATOR

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "type.h"
#include "spectrometer_structures.h"

template <class TYPE>
class SpectrometerConfigurationValidator
{
    public:
        SpectrometerConfigurationValidator(std::string config_file_path);

        std::vector<struct spec_config_param>
        validate(std::vector<struct spec_config_param>
                 config_vector);

        bool
        validate(struct spec_config_param
                 config_vector);

    private:
        std::vector<std::string>
        parseRow(std::string row);

        TYPE
        stringToNumber(std::string num_string);

        std::unordered_map<std::string, std::string>
        config_path_lookup;

        std::unordered_map<std::string, struct validator_map_entry<TYPE>>
        validator_lookup;

        std::unordered_map<std::string, bool(*)(TYPE, TYPE, TYPE)>
        check_function_lookup;

        void
        defineConfigPathLookup();

        void
        defineCheckFunctionLookup();

};

template <typename TYPE>
bool
checkInBounds(TYPE value, TYPE lower, TYPE upper)
{
    return value >= lower && value <= upper;
}

template <typename TYPE>
bool
checkInRange(TYPE val, TYPE lower, TYPE upper)
{
    for(TYPE num = lower; num <= upper; num++)
    {
        if(val == num)
        {
            return 1;
        }
    }
    return 0;
}

template<class TYPE>
void
SpectrometerConfigurationValidator<TYPE>::defineConfigPathLookup()
{
    config_path_lookup["uint32"] = 
    "/Users/anthonysteel/Documents/school/teams/spectrometer/config/uint32.csv";

    config_path_lookup["float"] = 
    "/Users/anthonysteel/Documents/school/teams/spectrometer/config/float.csv";

    config_path_lookup["uint16"] =
    "/Users/anthonysteel/Documents/school/teams/spectrometer/config/uint16.csv";

    config_path_lookup["uint8"] =
    "/Users/anthonysteel/Documents/school/teams/spectrometer/config/uint8.csv";
}

template<class TYPE>
void
SpectrometerConfigurationValidator<TYPE>::defineCheckFunctionLookup()
{
    check_function_lookup["checkInBounds"] = &checkInBounds;
    check_function_lookup["checkInRange"] = &checkInRange;
}

template<class TYPE>
std::vector<std::string>
SpectrometerConfigurationValidator<TYPE>::parseRow(std::string row)
{

    std::string column_value = std::string();
    std::vector<std::string> parsed;
    char COMMA = 0x2c, SPACE = 0x20;

    for(char& c : row)
    {
        if(c == COMMA)
        {
            parsed.push_back(column_value);
            column_value = std::string();
        }
        else if (c != SPACE)
        {
            column_value += c;
        }
    }

    parsed.push_back(column_value);

    return parsed;
}

template <class TYPE>
TYPE
SpectrometerConfigurationValidator<TYPE>::stringToNumber(std::string num_string)
{
    std::string::size_type sz;
    TYPE var = static_cast<TYPE>(std::stof(num_string, &sz));
    return var;
}

template <class TYPE>
SpectrometerConfigurationValidator<TYPE>::
SpectrometerConfigurationValidator(std::string type)
{
    std::string row;
    std::ifstream config_file;
    std::vector<std::vector<std::string>> parsed_rows;

    defineConfigPathLookup();
    defineCheckFunctionLookup();

    config_file.open(config_path_lookup[type]);

    if(config_file.is_open())
    {
        while(std::getline(config_file, row))
        {
            parsed_rows.push_back(parseRow(row));
        }

        for (const std::vector<std::string>&line : parsed_rows)
        {
            std::string param_name = line[0];

            TYPE lower = stringToNumber(line[1]),
                 upper = stringToNumber(line[2]);

            bool (*check_function) (TYPE, TYPE, TYPE) =
                check_function_lookup[line[3]];

            validator_lookup[param_name] =
                validator_map_entry<TYPE>
            {
                lower = lower,
                upper = upper,
                check_function = check_function
            };
        }

        config_file.close();
    }
}


template <class TYPE>
std::vector<struct spec_config_param>
SpectrometerConfigurationValidator<TYPE>::
validate(std::vector<struct spec_config_param> config_vector)
{
    std::vector<struct spec_config_param> validated_config_vector;

    for(const spec_config_param &param : config_vector)
    {
        validator_map_entry<TYPE> entry = validator_lookup[param.name];

        TYPE value = stringToNumber(param.value);

        if(entry.validate(value, entry.lower, entry.upper))
        {
            validated_config_vector.push_back(param);
        }
        else
        {
            validated_config_vector.push_back(spec_config_param {
                    "INVALID",
                    param.name,
                    param.value
                    });
        }
    }

    return validated_config_vector;
}

template <class TYPE>
bool
SpectrometerConfigurationValidator<TYPE>::
validate(struct spec_config_param param)
{
    std::vector<struct spec_config_param> validated_config_vector;

    validator_map_entry<TYPE> entry = validator_lookup[param.name];

    TYPE value = stringToNumber(param.value);

    if(entry.validate(value, entry.lower, entry.upper))
    {
        return true;
    }
    else
    {
        return false;
    }

}
#endif

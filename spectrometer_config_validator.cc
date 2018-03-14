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

        std::vector<struct spec_config_param<TYPE>>
        validate(std::vector<struct spec_config_param<TYPE>>
                       config_vector);


    private:
        std::vector<std::string>
        parseRow(std::string row);

        TYPE 
        stringToNumber(std::string num_string);

        std::unordered_map<std::string, struct validator_map_entry<TYPE>>
        validator_lookup; 

        std::unordered_map<std::string, bool(*)(TYPE, TYPE, TYPE)>
        check_function_lookup;

        void defineCheckFunctionLookup();

};

template <typename TYPE>
bool checkInBounds(TYPE value, TYPE lower, TYPE upper)
{
    return value >= lower && value <= upper;
}

template<class TYPE>
void
SpectrometerConfigurationValidator<TYPE>::defineCheckFunctionLookup()
{
    check_function_lookup["checkInBounds"] = &checkInBounds;
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
SpectrometerConfigurationValidator(std::string config_file_path)
{
    std::string row;
    std::ifstream config_file;
    std::vector<std::vector<std::string>> parsed_rows;

    defineCheckFunctionLookup();

    config_file.open(config_file_path);
    if(config_file.is_open())
    {
        while(std::getline(config_file, row))
        {
            parsed_rows.push_back(parseRow(row));
        }

        for (const std::vector<std::string> &row : parsed_rows)
        {
            std::string param_name = row[0]; 

            TYPE lower = stringToNumber(row[1]),
                   upper = stringToNumber(row[2]);

            bool (*check_function) (uint32, uint32, uint32) = 
            check_function_lookup[row[3]];

            validator_lookup[param_name] =
                validator_map_entry<TYPE>
                {
                    .lower = lower,
                    .upper = upper,
                    .validate = check_function
                };
        }

        config_file.close();
    }
}
    

template <class TYPE>
std::vector<struct spec_config_param<TYPE>>
SpectrometerConfigurationValidator<TYPE>::
validate(std::vector<struct spec_config_param<TYPE>> config_vector)
{
    std::vector<struct spec_config_param<TYPE>> validated_config_vector;

    for(const spec_config_param<TYPE> &param : config_vector)
    {
        validator_map_entry<TYPE> entry = validator_lookup[param.name];

        if(entry.validate(param.value, entry.lower, entry.upper))
        {
            validated_config_vector.push_back(param);
        }
    }

    return validated_config_vector;
}


int main()
{
    std::vector<struct spec_config_param<uint32>>
    configuration_vector = { 
        spec_config_param<uint32> {
            .name = "start_pixel",
            .value = 4100U
        },
        spec_config_param<uint32> {
            .name = "stop_pixel",
            .value = 15U
        }
    };

    SpectrometerConfigurationValidator<uint32>
    validator("./config/spectrometer_config.csv");

    std::vector<struct spec_config_param<uint32>>
    validated_configuration = validator.validate(configuration_vector);

    std::cout << std::endl;
    std::cout << "validated configuration vector" << std::endl;
    for(const auto& param : validated_configuration)
    {
        std::cout << "    " << param.name << std::endl;
    }

    std::cout << std::endl;
    std::cout << "unvalidated configuration vector" << std::endl;
    for(const auto& param : configuration_vector)
    {
        std::cout << "    " << param.name << std::endl;
    }

    return 0;
}

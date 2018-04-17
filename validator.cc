#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "type.h"
#include "validator_structures.h"
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

        std::vector<std::string>
        parseRow(std::string row);

        template <class TYPE>
        bool
        validate_entry(spec_config_param unvalidated_param,
                       validator_map_entry entry);


};

std::vector<std::string>
Validator::
parseRow(std::string row)
{
    std::string column_value = std::string();
    std::vector<std::string> parsed;
    char COMMA = 0x2c, SPACE = 0x20;

    for (char& c : row)
    {
        if (c == COMMA)
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

Validator::
Validator()
{
    std::string row;
    std::ifstream config_file;
    std::vector<std::vector<std::string>> parsed_rows;
    
    config_file.open("config/meas_config.csv");

    if (config_file.is_open())
    {
        while (std::getline(config_file, row))    
        {
            parsed_rows.push_back(parseRow(row));
        }

        for (const std::vector<std::string> &line : parsed_rows)
        {
            std::string type = line[0],
                        param_name = line[1],
                        lower = line[2],
                        upper = line[3];

            validator_lookup[param_name] = 
            validator_map_entry {
                type,
                lower,
                upper
            };
        }

        config_file.close();
    }
}


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

bool
Validator::
validate(spec_config_param unvalidated_param)
{
    spec_config_param valid_param;

    validator_map_entry entry = validator_lookup[unvalidated_param.name];

    if (entry.type == "uint32")
    {
        return validate_entry<uint32>(unvalidated_param, entry);
    }
    else if (entry.type == "uint16")
    {
        return validate_entry<uint16>(unvalidated_param, entry);
    }
    else if (entry.type == "uint8")
    {
        return validate_entry<uint8>(unvalidated_param, entry);
    }
    else if (entry.type == "float")
    {
        return validate_entry<float>(unvalidated_param, entry);
    }
    else
    {
        std::cout <<
        "Validator::Validate did not have an entry type matching: " <<
        "uint32, uint16, uint8, float" <<
        std::endl;
        return 0;
    }
}

int main()
{
    spec_config_param param = {
        "laser_wavelength",
        "50"
    };

    Validator spec_config_validator;

    std::cout << spec_config_validator.validate(param) << std::endl;

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

typedef unsigned int uint32;

typedef struct spectrometer_configuration_parameter 
{
    std::string name;
    uint32 value;
} spec_config_param;

struct validator_map_entry 
{
    uint32* m_variable;
    uint32 lower, upper;
    bool (* validate)(uint32, uint32, uint32);
}; 

class SpectrometerConfigurationValidator
{
    public:
        SpectrometerConfigurationValidator(std::string config_file_path);

        std::vector<struct spectrometer_configuration_parameter>
        validateUINT32(std::vector<struct spectrometer_configuration_parameter>
                       config_vector);


    private:
        // Helper methods and attributes 
        std::vector<std::string>
        parseRow(std::string row);

        uint32 
        stringToNumber(std::string num_string);

        std::unordered_map<std::string, struct validator_map_entry>
        validator_lookup; 

        std::unordered_map<std::string, bool(*)(uint32, uint32, uint32)>
        check_function_lookup;

        void defineCheckFunctionLookup();

};

bool checkInBounds(uint32 value, uint32 lower, uint32 upper)
{
    return value >= lower && value <= upper;
}

void
SpectrometerConfigurationValidator::defineCheckFunctionLookup()
{
    check_function_lookup["checkInBounds"] = &checkInBounds;
}

std::vector<std::string>
SpectrometerConfigurationValidator::parseRow(std::string row)
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

uint32 
SpectrometerConfigurationValidator::stringToNumber(std::string num_string)
{
    uint32 uint32_type = 0U;
    return std::stoi(num_string, nullptr, uint32_type);
}

SpectrometerConfigurationValidator::
SpectrometerConfigurationValidator(std::string config_file_path)
{
    std::string row;
    std::ifstream config_file;
    std::vector<std::vector<std::string>> parsed_row;

    defineCheckFunctionLookup();

    config_file.open(config_file_path);
    if(config_file.is_open())
    {
        while(std::getline(config_file, row))
        {
            parsed_row.push_back(parseRow(row));
        }
        for (const std::vector<std::string> &v : parsed_row)
        {
            std::string param_name = v[0], type = v[1]; 
            uint32 lower = stringToNumber(v[2]), upper = stringToNumber(v[3]);

            bool (*check_function) (uint32, uint32, uint32) = 
            check_function_lookup[v[4]];

            validator_lookup[param_name] =
                validator_map_entry 
                {
                    .lower = lower,
                    .upper = upper,
                    .validate = check_function
                };
        }

        config_file.close();
    }
}
    

std::vector<struct spectrometer_configuration_parameter>
SpectrometerConfigurationValidator::
validateUINT32(std::vector
               <struct spectrometer_configuration_parameter> config_vector)
{
    for(auto param=config_vector.begin(); param!=config_vector.end(); ++param)
    {
        validator_map_entry entry = validator_lookup[param->name];

        if(!entry.validate(param->value, entry.lower, entry.upper))
        {
            config_vector.erase(param);
        }
    }

    return config_vector;
}


int main()
{
    std::vector<struct spectrometer_configuration_parameter>
    configuration_vector = { 
        spec_config_param {
            .name = "start_pixel",
            .value = 4100U
        },
        spec_config_param {
            .name = "stop_pixel",
            .value = 15U
        }
    };

    SpectrometerConfigurationValidator 
    validator("./config/spectrometer_config.csv");

    std::vector<struct spectrometer_configuration_parameter>
    validated_configuration = validator.validateUINT32(configuration_vector);

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

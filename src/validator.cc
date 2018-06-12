#include "validator.h"

Validator::
Validator(std::string path_to_config)
{
    std::string row;
    std::ifstream config_file;
    std::vector<std::vector<std::string>> parsed_rows;
    Parser csv_parser;

    config_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        config_file.open(path_to_config);
    } catch (std::ifstream::failure e) {
        throw std::runtime_error("Validator config file failed to open. Check file path");
    }

    if (config_file.is_open()) {
        while (std::getline(config_file, row)) {
            parsed_rows.push_back(csv_parser.parseRow(row));
        }

        for (const std::vector<std::string> &line : parsed_rows) {
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

bool
Validator::
validate(spec_config_param unvalidated_param)
{
    spec_config_param valid_param;

    validator_map_entry entry = validator_lookup[unvalidated_param.name];

    if (entry.type == "uint32") {
        return validate_entry<uint32>(unvalidated_param, entry);
    } else if (entry.type == "uint16") {
        return validate_entry<uint16>(unvalidated_param, entry);
    } else if (entry.type == "uint8") {
        return validate_entry<uint8>(unvalidated_param, entry);
    } else if (entry.type == "float") {
        return validate_entry<float>(unvalidated_param, entry);
    } else {
        throw std::runtime_error(
            "Validator::Validate did not have an entry type matching: uint32, uint16, uint8, float");
    }
}

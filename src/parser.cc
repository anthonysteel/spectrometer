#include "parser.h"
#include "iostream"

std::vector<std::string>
Parser::
parseRow(std::string row)
{
    std::string column_value = std::string();
    std::vector<std::string> parsed;
    char COMMA = 0x2c, SPACE = 0x20;

    for (const char& c : row) {
        if (c == COMMA) {
            parsed.push_back(column_value);
            column_value = std::string();
        } else if (c != SPACE) {
            column_value += c;
        }
    }

    parsed.push_back(column_value);
    for (auto val : parsed) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return parsed;
}

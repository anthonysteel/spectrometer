#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <parser.h>

TEST(Parser, parseRow)
{
    std::string row;
    std::ifstream config_file;
    std::vector<std::vector<std::string>> parsed_rows;
    Parser csv_parser;
    
    config_file.open("/home/pi/spectrometer/test/parser.csv");

    if (config_file.is_open())
    {
        while (std::getline(config_file, row))    
        {
            parsed_rows.push_back(csv_parser.parseRow(row));
        }

        config_file.close();
    }

    std::vector<std::vector<std::string>> correct_parsed_rows;
    correct_parsed_rows = {
        {"uint8", "source_type", "0", "1", "checkInRange"},
        {"uint32", "integration_delay", "0x0", "0xFFFFFFF", "checkInBounds"}
    };

    for (int i = 0; i < correct_parsed_rows.size(); i++)
    {
        for (int j = 0; j < correct_parsed_rows[0].size(); j++)
        {
            EXPECT_EQ(parsed_rows[i][j], correct_parsed_rows[i][j]);
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

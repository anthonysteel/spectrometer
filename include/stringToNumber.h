#ifndef STRING_TO_NUMBER_H
#define STRING_TO_NUMBER_H

template <typename TYPE>
TYPE
stringToNumber(std::string num_string)
{
    std::string::size_type sz;
    TYPE var = static_cast<TYPE>(std::stof(num_string, &sz));
    return var;
}

#endif

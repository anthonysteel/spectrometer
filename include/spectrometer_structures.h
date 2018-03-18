#ifndef SPECTOMETER_STRUCTURES_H
#define SPECTOMETER_STRUCTURES_H

struct spec_config_param
{
    std::string type;
    std::string name;
    std::string value;
};

template <typename TYPE>
struct validator_map_entry 
{
    TYPE lower, upper;
    bool (* validate)(TYPE, TYPE, TYPE);
}; 
#endif


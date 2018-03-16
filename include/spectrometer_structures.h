#ifndef SPECTOMETER_STRUCTURES_H
#define SPECTOMETER_STRUCTURES_H

template <typename TYPE>
struct spec_config_param
{
    std::string name;
    TYPE value;
};

template <typename TYPE>
struct validator_map_entry 
{
    TYPE lower, upper;
    bool (* validate)(TYPE, TYPE, TYPE);
}; 
#endif


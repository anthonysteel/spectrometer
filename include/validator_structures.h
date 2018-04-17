#ifndef SPECTOMETER_STRUCTURES_H
#define SPECTOMETER_STRUCTURES_H

typedef struct 
{
    std::string name;
    std::string value;
} spec_config_param;

typedef struct 
{
    std::string type, lower, upper;
} validator_map_entry; 

#endif

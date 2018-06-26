#ifndef VALIDATOR_STRUCTURES_H 
#define VALIDATOR_STRUCTURES_H

typedef struct 
{
    std::string name;
    int value;
} spec_config_param;

typedef struct 
{
    std::string type, lower, upper;
} validator_map_entry; 

#endif

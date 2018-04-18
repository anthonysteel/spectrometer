#include "avaspec.h"
#include "validator.h"
#include "validator_structures.h"
#include "stringToNumber.h"

class Spectrometer
{
    public:
        Spectrometer(std::vector<spec_config_param> config_vector);

        void activate();
        
        std::vector<double> measure();
    private:
        MeasConfigType spec_config;
        void assignMeasConfigType(spec_config_param param);

        std::unordered_map<std::string, uint32*>
        UINT32_config_lookup;

        std::unordered_map<std::string, uint16*>
        UINT16_config_lookup;

        std::unordered_map<std::string, uint8*>
        UINT8_config_lookup;

        std::unordered_map<std::string, float*>
        FLOAT_config_lookup;

        void defineConfigLookup();

        Validator SpecConfigValidator;

        AvsHandle device_id;
};

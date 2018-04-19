#include "avaspec.h"
#include "validator.h"
#include "spectrometer_structures.h"
#include "stringToNumber.h"

class Spectrometer
{
    public:
        Spectrometer(std::vector<spec_config_param> config_vector);

        void activate();
        
        std::vector<double> measure();
    private:
        MeasConfigType spec_config;

        void defineConfigLookup();

        Validator SpecConfigValidator;

        AvsHandle device_id;
};

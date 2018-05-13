#ifndef SPECTROMETER_H
#define SPECTROMETER_H

#include "avaspec.h"
#include "validator.h"
#include "meas_config_type_builder.h"
#include "spectrometer_structures.h"
#include "stringToNumber.h"
#include <string>
#include <vector>
#include <unistd.h>
#include <math.h>

class Spectrometer
{
    public:
        Spectrometer(std::vector<spec_config_param> config_vector);

        void activate();
        
        std::vector<double> measure();

        float getThermistor();
    private:

        float voltageToCelsius(float analog_reading);

        void defineConfigLookup();

        MeasConfigType spec_config;

        Validator SpecConfigValidator;

        AvsHandle device_id;
};
#endif

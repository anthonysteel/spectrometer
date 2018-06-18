#ifndef SPECTROMETER_H
#define SPECTROMETER_H

#include "avaspec.h"
#include "validator.h"
#include "avs_interface.h"
#include "meas_config_type_builder.h"
#include "spectrometer_structures.h"
#include "stringToNumber.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <unistd.h>
#include <math.h>

class Spectrometer
{
    public:
        Spectrometer(AVSInterface *a, std::vector<spec_config_param> config_vector, std::string meas_config_filepath);

        void activate();
        void deactivate();
        
        std::vector<double> measure();

        float getThermistor();
    private:

        float voltageToCelsius(float analog_reading);

        void defineConfigLookup();

        MeasConfigType spec_config;

        Validator SpecConfigValidator;

        int device_id;

        AVSInterface *avs;

};
#endif

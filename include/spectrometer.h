
#ifndef SPECTROMETER_H_
#define SPECTROMETER_H_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sys/types.h>
#include <unistd.h>
#include <memory>

#include "avaspec.h"
#include "spectrometer_structures.h"
#include "spectrometer_config_validator.h"
#include "stringToNumber.h"

#include "AvaSpecConnection.h"


class Spectrometer
{
    public:
	Spectrometer(const std::vector<struct spec_config_param>& config_vector)
	: Spectrometer(config_vector, std::shared_ptr<AvaSpecConnection>(new AvaSpecConnection()))
	{}

        Spectrometer(
	    const std::vector<struct spec_config_param>& config_vector,
	    const std::shared_ptr<AvaSpecConnection>& avaspec);

        void activate();
        
        std::vector<double> measure();
    private:
        MeasConfigType spec_config;
        void assignMeasConfigType(struct spec_config_param param);

        std::unordered_map<std::string, uint32*>
        UINT32_config_lookup;

        std::unordered_map<std::string, uint16*>
        UINT16_config_lookup;

        std::unordered_map<std::string, uint8*>
        UINT8_config_lookup;

        std::unordered_map<std::string, float*>
        FLOAT_config_lookup;

        void defineConfigLookup();

        SpectrometerConfigurationValidator<uint32> UINT32_validator;
        SpectrometerConfigurationValidator<uint16> UINT16_validator;
        SpectrometerConfigurationValidator<uint8> UINT8_validator;
        SpectrometerConfigurationValidator<float> FLOAT_validator;

        AvsHandle device_id;
	std::shared_ptr<AvaSpecConnection> connector_;
};

#endif

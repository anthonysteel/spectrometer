#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <sys/types.h>
#include "avaspec.h"
#include "spectrometer_structures.h"
#include "spectrometer_config_validator.h"

class Spectrometer
{
    public:
        Spectrometer(std::vector<struct spec_config_param> config_vector);

    private:
        MeasConfigType spec_config;
        void assignMeasConfigType(struct spec_config_param param);

        std::unordered_map<std::string, uint32>
        UINT32_config_lookup;

        std::unordered_map<std::string, uint16>
        UINT16_config_lookup;

        std::unordered_map<std::string, uint8>
        UINT8_config_lookup;

        std::unordered_map<std::string, uint32>
        FLOAT_config_lookup;

        void defineConfigLookup();

        SpectrometerConfigurationvalidator UINT32_validator;
        SpectrometerConfigurationvalidator UINT16_validator;
        SpectrometerConfigurationvalidator UINT8_validator;
        SpectrometerConfigurationvalidator FLOAT_validator;
}

void
Spectrometer::defineConfigLookup()
{
    UINT32_config_lookup["start_pixel"] = &spec_config.m_StartPixel;
    UINT32_config_lookup["stop_pixel"] = &spec_config.m_StopPixel;
    UINT32_config_lookup["integration_delay"] = &spec_config
                                                .m_IntegrationDelay;
    UINT32_config_lookup["number_averages"] = &spec_config.m_NrAverages;
    UINT32_config_lookup["laser_delay"] = &spec_config.m_Control.m_LaserDelay;
    UINT32_config_lookup["laser_width"] = &spec_config.m_Control.m_LaserWidth;
    UINT16_config_lookup["smooth_pixel"] = &spec_config.m_Smoothing
                                                .m_SmoothPix;
    UINT16_config_lookup["strobe_control"] = &spec_config.m_Control
                                                .m_StrobeControl;
    UINT8_config_lookup["enable"] = &spec_config.m_CorDynDark.m_Enable;
    UINT8_config_lookup["forget_percentage"] = &spec_config.m_CorDynDark
                                              .m_ForgetPercentage;
    UINT8_config_lookup["smooth_model"] = &spec_config.m_Smoothing
                                         .m_SmoothModel;
    UINT8_config_lookup["mode"] = &spec_config.m_Trigger.m_Mode;
    UINT8_config_lookup["source"] = &spec_config.m_Trigger.m_Source;
    UINT8_config_lookup["source_type"] = &spec_config.m_Trigger.m_SourceType;
    FLOAT_config_lookup["laser_wavelength"] = &spec_config.m_Control
                                             .m_LaserWaveLength;
    FLOAT_config_lookup["integration_time"] = &spec_config.m_IntegrationTime;
}

void
Spectrometer::assignMeasConfigType(struct spec_config_param param)
{
    if(param.type == "uint32")
    {
        *UINT32_config_lookup[param.name] = param.value;
    }
    else if(param.type == "uint16")
    {
        *UINT16_config_lookup[param.name] = param.value;
    }
    else if(param.type == "uint8")
    {
        *UINT8_config_lookup[param.name] = param.value;
    }
    else if(param.type == "float")
    {
        *FLOAT_config_lookup[param.name] = param.value;
    }
}


Spectrometer::Spectrometer(std::vector<struct spec_config_param> config_vector)
{
    for(const struct spec_config_param& param : config_vector)
    {
        if(param.type == "uint32" && UINT32_validator.validate(param) 
           || param.type = "uint16" && UINT16_validator.validate(param) 
           || param.type = "uint8" && UINT8_validator.validate(param)
           || param.type = "float" && FLOAT_validator.validate(param))
        {
            assignMeasConfigType(param);
        }
    }

    setAvaSpecParameters(spec_config); 
    AVS_PrepareMeasure(a_hDevice, a_pMeasConfig);
}

void Spectrometer::activate()
{
	unsigned int ByteSet;

	int port = 1; // USB

	AvsIdentityType a_pList[30];

	AVS_Init(port); 

	AVS_UpdateUSBDevices();
	
	AVS_GetList( sizeof(a_pList), &ByteSet, a_pList );

	a_hDevice = AVS_Activate( &a_pList[0] );

}

void Spectrometer::setMeasureConfig()
{
	setAvaSpecParameters(a_pMeasConfig);	

	int msmt_prp_sts = AVS_PrepareMeasure(a_hDevice, a_pMeasConfig ); // measurement prepare status

	if(msmt_prp_sts == ERR_SUCCESS)
	{
		log("SCS", "Success: Spectrometer is configured");
	} 
	else 
	{
		log("ERR", "Error: Spectrometer configuration imcomplete");
	}

}

void Spectrometer::measure()
{
	int msmt_sts = AVS_MeasureCallback( a_hDevice, NULL, 1 );
	if(msmt_sts  == ERR_SUCCESS)
	{
		printf ("Measurement Ready\n");
	}
	else
	{
		printf ("%d\n", msmt_sts);
	}

	
	while( !AVS_PollScan( a_hDevice ) )
	{
		delay(10);
	}


	for(int j = 0; j < a_pMeasConfig -> m_Control.m_StoreToRam; j++)
	{
	   AVS_GetScopeData( a_hDevice, a_pTimeLabel, buffer);
	}

}

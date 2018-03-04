#include "avaspec.h"

class SpectrometerConfig 
{
    public:
        // Default constructor
        SpectrometerConfig();
        
        bool setStartPixel(unsigned short val, MeasConfigType* measConfig);
        bool setStopPixel(unsigned short val, MeasConfigType* measConfig);
        bool setIntegrationTime(float val, MeasConfigType* measConfig);
        bool setIntegrationDelay(unsigned int val, MeasConfigType* measConfig);
        bool setNumberAverages(unsigned int val, MeasConfigType* measConfig);
        bool setCorDynDark(DarkCorrectionType config,
                           MeasConfigType* measConfig);
        bool setSmoothing(SmoothingType config, MeasConfigType* measConfig);
        bool setTrigger(TriggerType config, MeasConfigType* measConfig);
        bool setControlSettings(ControlSettingsType config,
                                MeasConfigType* measConfig);
	MeasConfigType* getConfiguration() { return &config_; }
    
    private:

	MeasConfigType config_;
        enum class specConfigParams
        {
            START_PIXEL,
            STOP_PIXEL,
            INTEGRATION_TIME,
            INTEGRATION_DELAY,
            NUMBER_AVERAGES,
            COR_DYN_DARK,
            SMOOTHING,
            TRIGGER,
            CONTROL_SETTINGS
        };

	template<class TYPE>
        bool checkValRange(TYPE val, int lower, int upper);

	template<class TYPE>
	bool checkandSetVal(TYPE val, specConfigParams valConfig, int lower, int upper, MeasConfigType* measConfig);

	template<class TYPE>
        void setVal(TYPE val, 
                    specConfigParams config_type,
                    MeasConfigType* measConfig);

};


template<class TYPE>
bool SpectrometerConfig::checkValRange(TYPE val, int lower, int upper)
{
    return val >= lower && val <= upper;
}

template<class T>
void SpectrometerConfig::setVal(T val, specConfigParams config_type, MeasConfigType* measConfig)
{
    switch(config_type)
    {
        case specConfigParams::START_PIXEL:
            measConfig -> m_StartPixel = static_cast<decltype(measConfig->m_StartPixel)>(val);
            break;
        case specConfigParams::STOP_PIXEL:
            measConfig -> m_StopPixel = val;
            break;
        case specConfigParams::INTEGRATION_TIME:
            measConfig -> m_IntegrationTime = val;
            break;
        case specConfigParams::INTEGRATION_DELAY:
            measConfig -> m_IntegrationDelay = val;
            break;
        case specConfigParams::NUMBER_AVERAGES:
            measConfig -> m_NrAverages = val;
            break;
        case specConfigParams::COR_DYN_DARK:
            measConfig -> m_CorDynDark.m_Enable = val -> enable;
            measConfig -> m_CorDynDark.m_ForgetPercentage = val -> percentage;
            break;
        case specConfigParams::SMOOTHING:
            measConfig -> m_Smoothing.m_SmoothPix = val -> pixel;
            measConfig -> m_Smoothing.m_SmoothModel = val -> model;
            break;
        case specConfigParams::TRIGGER:
            measConfig -> m_Trigger.m_Mode = val -> mode;
            measConfig -> m_Trigger.m_Source = val -> source;
            measConfig -> m_Trigger.m_Source = val -> type;
            break;
        case specConfigParams::CONTROL_SETTINGS:
            measConfig -> m_Control.m_StrobeControl = val -> strobe;
            measConfig -> m_Control.m_LaserDelay = val -> delay;
            measConfig -> m_Control.m_LaserWidth = val -> width;
            measConfig -> m_Control.m_LaserWaveLength = val -> wavelength;
            measConfig -> m_Control.m_StoreToRam = val -> store_to_ram;
            break;
    }
}

template<class T>
bool SpectrometerConfig::checkandSetVal(T val, specConfigParams valConfig, int lower, int upper, MeasConfigType* measConfig)
{
    if(!checkValRange(val, lower, upper))
    {
        setVal(val, valConfig, measConfig)
        return 1;
    }
    else
    {
        return 0;
    }
}

bool SpectrometerConfig::setStartPixel(unsigned short val,
                                       MeasConfigType* measConfig)
{
    int LOWER = 0;
    int UPPER = 4095;
    specConfigParams valConfig = specConfigParams::START_PIXEL;
    return checkandSetVal(val, valConfig, LOWER, UPPER, measConfig)
}

bool SpectrometerConfig::setStopPixel(unsigned short val,
                                      MeasConfigType* measConfig)
{
    int LOWER = 0;
    int UPPER = 4095;
    specConfigParams valConfig = specConfigParams::STOP_PIXEL;
    return checkandSetVal(val, valConfig, LOWER, UPPER, measConfig)
}

bool SpectrometerConfig::setIntegrationTime(float val,
                                            MeasConfigType* measConfig)
{
    int LOWER = 0.002;
    int UPPER = 600000;
    specConfigParams valConfig = specConfigParams::INTEGRATION_TIME;
    return checkandSetVal(val, valConfig, LOWER, UPPER, measConfig)
}

bool SpectrometerConfig::setIntegrationDelay(unsigned int val,
                                             MeasConfigType* measConfig)
{
    int LOWER = 0;
    int UPPER = 0xFFFFFFFF;
    specConfigParams valConfig = specConfigParams::INTEGRATION_DELAY;
    return checkandSetVal(val, valConfig, LOWER, UPPER, measConfig)
}


bool SpectrometerConfig::setNumberAverages(unsigned int val,
                                           MeasConfigType* measConfig)
{
    int LOWER = 1;
    int UPPER = 0xFFFFFFFF;
    specConfigParams valConfig = specConfigParams::NUMBER_AVERAGES;
    return checkandSetVal(val, valConfig, LOWER, UPPER, measConfig)
}

bool SpectrometerConfig::setCorDynDark(DarkCorrectionType val,
                                       MeasConfigType* measConfig)
{
    int LOWER = 0;
    int UPPER = 4095;
    specConfigParams valConfig = specConfigParams::COR_DYN_DARK;
    return checkandSetVal(val, valConfig, LOWER, UPPER, measConfig)
}

bool SpectrometerConfig::setSmoothing(SmoothingType val,
                                      MeasConfigType* measConfig)
{
    int LOWER = 0;
    int UPPER = 4095;
    specConfigParams valConfig = specConfigParams::SMOOTHING;
    return checkandSetVal(val, valConfig, LOWER, UPPER, measConfig)
}

bool SpectrometerConfig::setTrigger(TriggerType val,
                                    MeasConfigType* measConfig)
{
    int LOWER = 0;
    int UPPER = 4095;
    specConfigParams valConfig = specConfigParams::TRIGGER;
    return checkandSetVal(val, valConfig, LOWER, UPPER, measConfig)
}

bool SpectrometerConfig::setControlSettings(ControlSettingsType val,
                                            MeasConfigType* measConfig)
{
    int LOWER = 0;
    int UPPER = 4095;
    specConfigParams valConfig = specConfigParams::CONTROL_SETTINGS;
    return checkandSetVal(val, valConfig, LOWER, UPPER, measConfig)
}

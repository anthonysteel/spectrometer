#include "avaspec.h"

class SpectrometerConfig 
{
    public:
        SpectrometerConfig();
        
        bool setStartPixel(unsigned short val);
        bool setStopPixel(unsigned short val);
        bool setIntegrationTime(float val);
        bool setIntegrationDelay(unsigned int val);
        bool setNumberAverages(unsigned int val);
        // Dynamic Dark Correction Type
        bool setEnable(unsigned char val);
        bool setForgetPercentage(unsigned char val);
        // Smoothing Type
        bool setSmoothPixel(unsigned short val);
        bool setSmoothModel(unsigned char val);
        // Trigger type
        bool setMode(unsigned char val);
        bool setSource(unsigned char val);
        bool setSourceType(unsigned char val);
        // Control Settings
        bool setStrobeControl(unsigned short val);
        bool setLaserDelay(unsigned int val);
        bool setLaserWidth(unsigned int val);
        bool setLaserWavelength(float val);
        bool setStoreToRam(unsigned short val);

        MeasConfigType* getConfigType() { return &config_; }
    
    private:
        MeasConfigType config_;
        enum class specConfigParams
        {
            START_PIXEL,
            STOP_PIXEL,
            INTEGRATION_TIME,
            INTEGRATION_DELAY,
            NUMBER_AVERAGES,
            ENABLE,
            FORGET_PERCENTAGE,
            SMOOTH_PIXEL,
            SMOOTH_MODEL,
            MODE,
            SOURCE,
            SOURCE_TYPE,
            STROBE_CONTROL,
            LASER_DELAY,
            LASER_WIDTH,
            LASER_WAVELENGTH,
            STORE_TO_RAM
        };

        template<class TYPE>
        bool checkValRange(TYPE val, int lower, int upper);

        template<class TYPE>
        void setVal(TYPE val, 
                    specConfigParams config_type,
                    MeasConfigType* config_);

        template<class TYPE>
        bool checkandSetVal(TYPE val, specConfigParams valConfig,
                            int lower, int upper);

};


template<class TYPE>
bool SpectrometerConfig::checkValRange(TYPE val, int lower, int upper)
{
    return val >= lower && val <= upper;
}

template<class T>
void SpectrometerConfig::setVal(T val, specConfigParams config_type)
{
    switch(config_type)
    {
        case specConfigParams::START_PIXEL:
            config_ -> m_StartPixel = static_cast<decltype(
                                      config_ -> m_StartPixel)>(val);
            break;
        case specConfigParams::STOP_PIXEL:
            config_ -> m_StopPixel = static_cast<decltype(
                                     config_ -> m_StopPixel)>(val);
            break;
        case specConfigParams::INTEGRATION_TIME:
            config_ -> m_IntegrationTime = static_cast<decltype(
                                           config_ -> m_IntegrationTime)
                                           -> (val);
            break;
        case specConfigParams::INTEGRATION_DELAY:
            config_ -> m_IntegrationDelay = static_cast<decltype(
                                            config_ -> m_IntegrationDelay)
                                            -> (val);
            break;
        case specConfigParams::NUMBER_AVERAGES:
            config_ -> m_NrAverages = static_cast<decltype(
                                      config_ -> m_NrAverages)
                                      -> (val);
            break;
        case specConfigParams::ENABLE:
            config_ -> m_CorDynDark.m_Enable = static_cast<decltype(
                                               config_ -> m_CorDynDark.m_Enable)
                                                -> (val);
            break;
        case specConfigParams::FORGET_PERCENTAGE:
            config_ -> m_CorDynDark.m_ForgetPercentage = static_cast<decltype(
                                    config_ -> m_CorDynDark.m_ForgetPercentage)
                                    -> (val);
            break;
        case specConfigParams::SMOOTH_PIXEL:
            config_ -> m_Smoothing.m_SmoothPix = static_cast<decltype(
                                            config_ -> m_Smoothing.m_SmoothPix)
                                            -> (val);
            break;
        case specConfigParams::SMOOTH_MODEL:
            config_ -> m_Smoothing.m_SmoothModel = static_cast<decltype(
                                          config_ -> m_Smoothing.m_SmoothModel)
                                          -> (val);
            break;
        case specConfigParams::MODE:
            config_ -> m_Trigger.m_Mode = static_cast<decltype(
                                          config -> m_Trigger.m_Mode)
                                          -> (val);
            break;
        case specConfigParams::SOURCE:
            config_ -> m_Trigger.m_Source = static_cast<decltype(
                                            config_ -> m_Trigger.m_Source)
                                            -> (val);
            break;
        case specConfigParams::SOURCE_TYPE:
            config_ -> m_Trigger.m_SourceType = static_cast<decltype(
                                             config_ -> m_Trigger.m_SourceType)
                                             -> val;
            break;
        case specConfigParams::STROBE_CONTROL:
            config_ -> m_Control.m_StrobeControl = static_cast<decltype(
                                          config_ -> m_Control.m_StrobeControl)
                                          -> (val);
            break;
        case specConfigParams::LASER_DELAY:
            config_ -> m_Control.m_LaserDelay = static_cast<decltype(
                                             config_ -> m_Control.m_LaserDelay)
                                             -> (val);
            break;
        case specConfigParams::LASER_WIDTH:
            config_ -> m_Control.m_LaserWidth = static_cast<decltype(
                                             config_ -> m_Control.m_LaserWidth)
                                             -> (val);
            break;
        case specConfigParams::LASER_WAVELENGTH:
            config_ -> m_Control.m_LaserWaveLength = static_cast<decltype(
                                        config_ -> m_Control.m_LaserWaveLength)
                                        -> val;
        case specConfigParams::STORE_TO_RAM:
            config_ -> m_Control.m_StoreToRam = static_cast<decltype(
                                            config_ -> m_Control.m_StoreToRam)
                                            -> val;
            break;
    }
}

template<class T>
bool SpectrometerConfig::checkandSetVal(specConfigParams val_type,
                                        T val, int lower, int upper)
{
    if(checkValRange(val, lower, upper))
    {
        setVal(val, val_type);
        return 1;
    }
    else
    {
        return 0;
    }
}

bool SpectrometerConfig::setStartPixel(unsigned short val)
{
    return checkandSetVal(specConfigParams::START_PIXEL,
                          val, 0, 4095);
}

bool SpectrometerConfig::setStopPixel(unsigned short val)
{
    return checkandSetVal(specConfigParams::STOP_PIXEL,
                          val, 0, 4095);
}

bool SpectrometerConfig::setIntegrationTime(float val)
{
    return checkandSetVal(specConfigParams::INTEGRATION_TIME, 
                          val, 0.002, 600000);
}

bool SpectrometerConfig::setIntegrationDelay(unsigned int val)
{
    return checkandSetVal(specConfigParams::INTEGRATION_DELAY,
                          val, 0, 0xFFFFFFFF);
}

bool SpectrometerConfig::setNumberAverages(unsigned int val)
{
    return checkandSetVal(specConfigParams::NUMBER_AVERAGES,
                          val, 1, 0xFFFFFFFF);
}

bool SpectrometerConfig::setEnable(unsigned char val)
{
    return checkandSetVal(specConfigParams::ENABLE,
                          val, 0, 1);
}

bool SpectrometerConfig::setForgetPercentage(unsigned char val)
{
    return checkandSetVal(specConfigParams::FORGET_PERCENTAGE,
                          val, 0, 100);
}

bool SpectrometerConfig::setSmoothPixel(unsigned short val)
{
    return checkandSetVal(specConfigParams::SMOOTH_PIXEL,
                          val, 0, 2048);
}

bool SpectrometerConfig::setSmoothModel(unsigned char val)
{
    return checkandSetVal(specConfigParams::SMOOTH_MODEL,
                          val, 0, 0);
}

bool SpectrometerConfig::setMode(unsigned char val)
{
    return checkandSetVal(SpectrometerConfig::MODE,
                         val, 0, 2);
}

bool SpectrometerConfig::setSource(unsigned char val)
{
    return checkandSetVal(SpectrometerConfig::SOURCE,
                         val, 0, 1);
}

bool SpectrometerConfig::setSourceType(unsigned char val)
{
    return checkandSetVal(SpectrometerConfig::SOURCE_TYPE,
                          val, 0, 1);
}

bool SpectrometerConfig::setStrobeControl(unsigned short val)
{
    return checkandSetVal(SpectrometerConfig::STROBE_CONTROL,
                          val, 0, 0xFFFF);
}

bool SpectrometerConfig::setLaserDelay(unsigned int val)
{
    return checkandSetVal(SpectrometerConfig::LASER_DELAY,
                          val, 0, 0xFFFFFFFF);
}

bool SpectrometerConfig::setLaserWidth(unsigned int val)
{
    return checkandSetVal(SpectrometerConfig::LASER_WIDTH,
                          val, 0, 0xFFFF);
}

bool SpectrometerConfig::setLaserWavelength(float val)
{
    return checkandSetVal(SpectrometerConfig::LASER_WAVELENGTH,
                          val, 0, 0xFFFF);
}

bool SpectrometerConfig::setStoreToRam(unsigned short val)
{
    return checkandSetVal(SpectrometerConfig::STORE_TO_RAM,
                          val, 0, 0xFFFF);
}

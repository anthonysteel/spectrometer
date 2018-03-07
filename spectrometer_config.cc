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

        unsigned short getStartPixel(unsigned short val);
        unsigned short getStopPixel(unsigned short val);
        float getIntegrationTime(float val);
        unsigned int getIntegrationDelay(unsigned int val);
        unsigned int getNumberAverages(unsigned int val);
        // Dynamic Dark Correction Type
        unsigned char getEnable(unsigned char val);
        unsigned char getForgetPercentage(unsigned char val);
        // Smoothing Type
        unsigned short getSmoothPixel(unsigned short val);
        unsigned char getSmoothModel(unsigned char val);
       // Trigger type
        unsigned char getMode(unsigned char val);
        unsigned char getSource(unsigned char val);
        unsigned char getSourceType(unsigned char val);
        // Control Settings
        unsigned short getStrobeControl(unsigned short val);
        unsigned int getLaserDelay(unsigned int val);
        unsigned int getLaserWidth(unsigned int val);
        float getLaserWavelength(float val);
        unsigned short getStoreToRam(unsigned short val);

    private:
        unsigned short _start_pixel;
        unsigned short _stop_pixel;
        float _integration_time;
        unsigned int _integration_delay;
        unsigned int _number_averages;
        unsigned char _enable;
        unsigned char _forget_percentage;
        unsigned short _smooth_pixel;
        unsigned char _smooth_model;
        unsigned char _mode;
        unsigned char _source;
        unsigned char _source_type;
        unsigned short _strobe_control;
        unsigned int _laser_delay;
        unsigned int _laser_width;
        float _laser_wavelength;
        unsigned short _store_to_ram;


};

template<class TYPE>
bool SpectrometerConfig::setVal(TYPE* _property,
                                bool (*comparisonFunction) (TYPE, TYPE, TYPE),
                                TYPE val, TYPE lower, TYPE upper)
{
    if(comparisonFunction(val, lower, upper))
    {
        *_property = val;
        return 1;
    }
    else
    {
        return 0;
    }
}
                                  

template<class TYPE>
bool SpectrometerConfig::boundedComparison(TYPE val, TYPE lower, TYPE upper)
{
    return val >= lower && val <= upper;
}

bool SpectrometerConfig::setStartPixel(unsigned short val)
{
    unsigned short lower = 0, upper = 4095;
    return setVal(&_start_pixel, &boundedComparison, val, lower, upper)
}

bool SpectrometerConfig::setStopPixel(unsigned short val)
{
    unsigned short lower = 0, upper = 4095;
    return setVal(&_stop_pixel, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setIntegrationTime(float val)
{
    float lower = 0.002, upper = 600000.0;
    return setVal(&_integration_time, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setIntegrationDelay(unsigned int val)
{
    unsigned int lower = 0x0, upper = 0xFFFFFFFF;
    return setVal(&_integration_delay, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setNumberAverages(unsigned int val)
{
    unsigned int lower = 0x1, upper = 0xFFFFFFFF;
    return setVal(&_number_averages, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setEnable(unsigned char val)
{
    unsigned char lower = 0, upper = 1;
    return setVal(&_enable, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setForgetPercentage(unsigned char val)
{
    unsigned char lower = 0, upper = 100;
    return setVal( _forget_percentage, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setSmoothPixel(unsigned short val)
{
    unsigned short lower = 0, upper = 2048;
    return setVal(&_smooth_pixel, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setSmoothModel(unsigned char val)
{
    unsigned char lower = 0, upper = 0;
    return setVal(&_smooth_model, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setMode(unsigned char val)
{
    unsigned char lower = 0, upper = 2;
    return setVal(&_mode, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setSource(unsigned char val)
{
    unsigned char lower = 0, upper = 1;
    return setVal(&_source, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setSourceType(unsigned char val)
{
    unsigned char lower = 0, upper = 1;
    return setVal(&_source_type, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setStrobeControl(unsigned short val)
{
    unsigned short lower = 0x0, upper = 0xFFFF;
    return setVal(&_strobe_control, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setLaserDelay(unsigned int val)
{
    unsigned int lower = 0, upper = 0xFFFFFFFF;
    return setVal(&_laser_delay, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setLaserWidth(unsigned int val)
{
    unsigned int lower = 0, upper = 0xFFFF;
    return setVal(&_laser_width, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setLaserWavelength(float val)
{
    float lower = 0, upper = 0xFFFF;
    return setVal(&_laser_wavelength, &boundedComparison, val, lower, upper);
}

bool SpectrometerConfig::setStoreToRam(unsigned short val)
{
    unsigned short lower = 0, upper = 0xFFFF;
    return setVal(&_store_to_ram, &boundedComparison, val, lower, upper);
}

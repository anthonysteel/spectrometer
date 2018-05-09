# AvaSpec Mini Spectrometer

This library allows data to be read from an AvaSpec Mini Spectrometer.
The source files are located in the ```src``` directory. 
The interface with the AvaSpec Mini is implemented as a spectrometer class 
in ```src/spectrometer.cc```.
The constructor accepts a configuration ```vector``` with 
```spec_config_param``` values. ```spec_config_param``` are a struct with two
properties ```name``` and ```value```. AvaSpec parameters can be set in the
configuration vector by defining ```spec_config param```'s. For example:
```cpp
std::vector<spec_config_param> config_vector =
{
    {"start_pixel", "0"},
    {"stop_pixel", "2047"},
    {"integration_time", "100"},
    {"integration_delay", "0"},
    {"number_averages", "1"},
    {"enable", "0"},
    {"forget_percentage", "100"},
    {"smooth_pixel", "0"},
    {"smooth_model", "0"},
    {"mode", "0"},
    {"source", "0"},
    {"source_type", "0"},
    {"strobe_control", "0"},
    {"laser_delay", "0"},
    {"laser_width", "10000"},
    {"laser_wavelength", "785"},
    {"store_to_ram", "1"}
};

Spectrometer AvaSpecMini(config_vector);
AvaSpecMini.activate();
```
This defines a standard spectrometer configuration, instatiates, and activates
the spectrometer. The spectrometer has a ```measure()``` method which returns
a ```vector``` of ```doubles``` where each index corresponds to a bin at a 
given frequency and the value is the count at that frequency. For example:

```cpp
std::vector<double> data = AvaSpecMini.measure();
```
The class will check the values entered in the ```config_vector``` against the
upper and lower bounds set for that value in the AvaSpec documentation. 


On Linux, the program using the spectrometer class must be run with ```sudo``` 
privileges otherwise the program will not have access to the AvaSpec hardware.
The spectrometer library ```libavs``` (distributed by AvaSpec)
must be installed.

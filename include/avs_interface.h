#ifndef AVS_INTERFACE_H
#define AVS_INTERFACE_H

#include "meas_config_type_builder.h"

class AVSInterface
{
  private:

  public:
    virtual int Init(const int &usb_port) = 0;
    virtual int Activate(const int &device_number) = 0;
    virtual void Deactivate(const int &device_id) = 0;
    virtual int UpdateUSBDevices() = 0;

    virtual void PrepareMeasure(const int &device_id, MeasConfigType *spec_config) = 0;
    virtual void Measure(const int &device_id, const short &num_measurements) = 0;
    virtual int PollScan(const int &device_id) = 0;

    virtual void GetScopeData(const int &device_id, unsigned int *time_label, double *data_buffer) = 0;
    virtual void GetAnalogIn(const int &device_id, const int &analog_input_id, float *analog_reading) = 0;
};
#endif

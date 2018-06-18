#ifndef AVS_WRAPPER_H
#define AVS_WRAPPER_H

#include "avaspec.h"
#include "avs_exception.h"
#include "meas_config_type_builder.h"

class AVSWrapper
{
  private:
    AvsIdentityType device_id_info[30];
    AVSException SpecException;

  public:
    int Init(const int &usb_port);
    int Activate(const int &device_number);
    void Deactivate(const int &device_id);
    // TODO split UpdateUSBDevices into two separate methods
    int UpdateUSBDevices();

    void PrepareMeasure(const int &device_id, MeasConfigType *spec_config);
    void Measure(const int &device_id, const short &num_measurements);
    int PollScan(const int &device_id);

    void GetScopeData(const int &device_id, unsigned int *time_label, double *data_buffer);
    void GetAnalogIn(const int &device_id, 
             const int &analog_input_id, float *analog_reading);
};
#endif

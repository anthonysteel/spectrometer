#include "avs_wrapper.h"

int
AVSWrapper::Init(const int &usb_port)
{
  int init_return = AVS_Init(usb_port);
  if (init_return < 0) {
    throw std::runtime_error("AVS_Init failed with: "
                            + SpecException.lookup(init_return));
  } else if (init_return == 0) {
    throw std::runtime_error("AVS_Init failed with: NO_DEVICE_FOUND");
  }

  return init_return;
}

int
AVSWrapper::Activate(const int &device_number)
{
  int activate_return = AVS_Activate(&device_id_info[device_number]);
  if (activate_return < 0) {
    throw std::runtime_error("AVS_Activate failed with: "
                            + SpecException.lookup(activate_return));
  }

  return activate_return;
}

void
AVSWrapper::Deactivate(const int &device_id)
{
  bool deactivate_return = AVS_Deactivate(device_id);
  if (!deactivate_return) {
    throw std::runtime_error("Spectrometer failed to deactivate, device ID incorrect");
  }
}

int
AVSWrapper::UpdateUSBDevices()
{
  int update_usb_return = AVS_UpdateUSBDevices();
  unsigned int required_bytes;

  if (update_usb_return < 0) {
      throw std::runtime_error("AVS_UpdateUSBDevices failed with: "
                              + SpecException.lookup(update_usb_return));
  } else if (update_usb_return == 0) {
      throw std::runtime_error("AVS_UpdateUSBDevices failed with: NO_DEVICE_FOUND");
  }

  int getlist_return = AVS_GetList(sizeof(device_id_info),
                                  &required_bytes, device_id_info);
  if (getlist_return < 0) {
      throw std::runtime_error("AVS_GetList failed with: "
                              + SpecException.lookup(getlist_return));
  } else if (getlist_return == 0) {
      throw std::runtime_error("AVS_GetList failed with: NO_DEVICE_FOUND");
  }
 
  return getlist_return;
}

void
AVSWrapper::PrepareMeasure(const int &device_id, MeasConfigType *spec_config)
{
  int prepare_measure_return = AVS_PrepareMeasure(device_id, spec_config);
  if (prepare_measure_return >= 0) {
    throw std::runtime_error("AVS_PrepareMeasure failed with: "
                            + SpecException.lookup(prepare_measure_return));
  }
}

void
AVSWrapper::Measure(const int &device_id, const short &num_measurements)
{
  int measure_callback_return = AVS_MeasureCallback(device_id, NULL, 1);
  if (measure_callback_return != 0) {
    throw std::runtime_error("AVS_MeasureCallback failed with: "
                            + SpecException.lookup(measure_callback_return));
  }
}

int
AVSWrapper::PollScan(const int &device_id) {
  int pollscan_return = AVS_PollScan(device_id);
  if (pollscan_return != 0) {
    throw std::runtime_error("AVS_PollScan failed with: "
                            + SpecException.lookup(pollscan_return));
  }

  return pollscan_return;
}

void
AVSWrapper::GetScopeData(const int &device_id, unsigned int *time_label, double *data_buffer) {
  int get_data_return = AVS_GetScopeData(device_id, time_label, data_buffer);
  if (get_data_return != 0) {
      throw std::runtime_error("AVS_GetScopeData threw: "
                              + SpecException.lookup(get_data_return));
  }
}

void
AVSWrapper::GetAnalogIn(const int &device_id, const int &analog_input_id, float *analog_reading) {
  int analog_in_return = AVS_GetAnalogIn(device_id, analog_input_id, analog_reading);
    
  if (analog_in_return != 0) {
      throw std::runtime_error("AVS_GetAnalogIn failed with: "
                              + SpecException.lookup(analog_in_return));
  }
}

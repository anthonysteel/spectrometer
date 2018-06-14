#include "gtest/gtest.h"
#include "avs_wrapper.h"
#include <vector>

TEST(AVSWrapper, deactivate)
{
  int usb_port = 0;
  int device_number = 0;

  AVSWrapper avs(usb_port);
  int device_id = avs.Activate(device_number);

  avs.Deactivate(device_id);
}

TEST(AVSWrapper, measure)
{
  int usb_port = 0;
  int device_number = 0;
  int num_measurements = 1;

  std::vector<spec_config_param> config_vector;
  config_vector = {
      {"startup_pixel", "0"},
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
  MeasConfigTypeBuilder meas_config_type_builder;
  MeasConfigType spec_config = meas_config_type_builder.build(config_vector);

  AVSWrapper avs(usb_port);
  int device_id = avs.Activate(device_number);

  avs.PrepareMeasure(device_id, spec_config);
  avs.Measure(device_id, num_measurements);

  avs.PollScan(device_id);

  double *data_buffer = new double;
  unsigned int *time_label = new unsigned int;
  
  avs.GetScopeData(device_id, time_label, data_buffer);

  avs.Deactivate(device_id);
}

TEST(AVSWrapper, analog)
{
  int usb_port = 0;
  int device_number = 0;

  AVSWrapper avs(usb_port);
  int device_id = avs.Activate(device_number);

  float *analog_reading = new float;
  avs.GetAnalogIn(device_id, 0, analog_reading);

  avs.Deactivate(device_id);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

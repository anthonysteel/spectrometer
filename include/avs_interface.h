#include "avaspec.h"
#include "avs_exception.h"

class AVSInterface
{
    private:
        AvsIdentityType device_id_info[30];
        AVSException SpecException;

        int Init(const int &usb_port);

    public:
        AVSInterface(const int &usb_port);

        // int Init(const int &usb_port);
        int Activate(const int &device_number);
        void Deactivate(const int &device_id);
        int UpdateUSBDevices(int *required_bytes);

        void PrepareMeasure(const int &device_id);
        void Measure(const int &device_id, const short &num_measurements);
        int PollScan(const int &device_id);

        void GetScopeData(const int &device_id, double *data_buffer);
        void GetAnalogIn(const int &device_id, 
            const int &analog_input_id, float *analog_reading);

        char serial_number();
        char name();
        int device_id();
}

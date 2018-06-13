#include "avs_interface.h"

AVSInterface::AVSInterface(const int &usb_port)
{
    Init(usb_port);
    UpdateUSBDevices();
    GetDeviceInfo();
}

int
AVSInterface::Init(const int &usb_port)
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
AVSInterface::Activate(const int &device_number)
{
    int activate_return = AVS_Activate(&device_id_info[device_number]);
    if (activate_return < 0) {
        throw std::runtime_error("AVS_Activate failed with: "
                                + SpecException.lookup(activate_return));
    }

    return activate_return;
}

void
AVSInterface::Deactivate(const int &device_id)
{
    bool deactivate_return = AVS_Deactivate(device_id);
    if (!deactivate_return) {
        throw std::runtime_error("Spectrometer failed to deactivate, device ID incorrect");
    }
}

int
AVSInterface::UpdateUSBDevices(int *required_bytes) {
    int update_usb_return = AVS_UpdateUSBDevices();
    if (update_usb_return < 0) {
        throw std::runtime_error("AVS_UpdateUSBDevices failed with: "
                                + SpecException.lookup(update_usb_return));
    } else if (update_usb_return == 0) {
        throw std::runtime_error("AVS_UpdateUSBDevices failed with: NO_DEVICE_FOUND");
    }

    unsigned int required_bytes;
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

#include "avs_exception.h"

std::string
AVSException::
lookup(int return_value)
{
    switch (return_value)
    { 
        case 0:
            return "ERR_SUCCESS";

        case -1:
            return "ERR_INVALID_PARAMETER";

        case -2:
            return "ERR_OPERATION_NOT_SUPPORTED";

        case -3:
            return "ERR_DEVICE_NOT_FOUND";

        case -4:
            return "ERR_INVALID_DEVICE_ID";

        case -5:
            return "ERR_OPERATION_PENDING";

        case -6:
            return "ERR_TIMEOUT";
        
        case -8:
            return "ERR_INVALID_MEAS_DATA";

        case -9:
            return "ERR_INVALID_SIZE";

        case -10:
            return "ERR_INVALID_SIZE";

        case -11:
            return "ERR_INVALID_INT_TIME";

        case -12:
            return "ERR_INVALID_COMBINATION";

        case -14:
            return "ERR_NO_MEAS_BUGGER_AVAIL";

        case -15:
            return "ERR_UNKNOWN";

        case -17:
            return "ERR_NO_SPECTRA_IN_RAM";

        case -18:
            return "ERR_INVALID_DLL_VERSION";

        case -19:
            return "ERR_NO_MEMORY";

        case -20:
            return "ERR_DLL_INITIALISATION";

        case -21:
            return "ERR_INVALID_STATE";

        case -22:
            return "ERR_INVALID_REPLY";

        case -23:
            return "Reserved";

        case -24:
            return "ERR_ACCESS";

        case -100:
            return "ERR_INVALID_PARAMETER_NR_PIXEL";

        case -101:
            return "ERR_INVALID_ADC_GAIN";

        case -102:
            return "ERR_INVALID_PARAMETER_ADC_OFFSET";

        case -110:
            return "ERR_INVALID_MEASPARAM_AVG_SAT2";
        
        case -111:
            return "ERR_INVALID_MEASPARAM_AVG_RAM";

        case -112:
            return "ERR_INVALID_MEASPARAM_SYNC_RAM";

        default:
            return "UNDEFINED ERROR";
    }
}

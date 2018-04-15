/////////////////////////
// Copyright QSAT 2018 //
/////////////////////////

#ifndef AVA_SPEC_CONNECTION_H_
#define AVA_SPEC_CONNECTION_H_

#include "avaspec.h"

/**
 * Wrapper around the avaspec library, which allows for mocking
 */
class AvaSpecConnection
{
public:
    AvaSpecConnection()
    {}

    virtual ~AvaSpecConnection()
    {}

    virtual auto Init( short port ) -> DLL_INT
    {
        return AVS_Init(port);
    }

    virtual auto Done() -> DLL_INT
    {
        return AVS_Done();
    }

    virtual auto UpdateUSBDevices() -> DLL_INT
    {
       return AVS_UpdateUSBDevices();
    }
    
    virtual auto GetList(
        unsigned int listSize,
        unsigned int* requiredSize,
        AvsIdentityType* list) -> DLL_INT
    {
        return AVS_GetList(listSize, requiredSize, list);
    }

    virtual auto Activate(AvsIdentityType* deviceId) -> DLL_INT
    {
        return AVS_Activate(deviceId);
    }

    virtual auto MeasureCallback(
        AvsHandle device,
        void (*__Done)(AvsHandle*, int*),
        short nmsr) -> DLL_INT
    {
        return AVS_MeasureCallback(device,__Done,nmsr);
    }

    virtual auto PollScan(AvsHandle device) -> DLL_INT
    {
        return AVS_PollScan(device);
    }

    virtual auto GetScopeData(
        AvsHandle device, 
        unsigned int* timeLabel, 
        double* spectrum ) -> DLL_INT
    {
        AVS_GetScopeData(device, timeLabel, spectrum);
    }

private:
    short port_ = 0;
};

#endif
/* vim: set ts=4 sw=4 et :*/

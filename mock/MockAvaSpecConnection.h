
#ifndef MOCK_AVASPEC_CONNECTION_H_
#define MOCK_AVASPEC_CONNECTION_H_

#include "gmock/gmock.h"
#include "AvaSpecConnection.h"

class MockAvaSpecConnection : public AvaSpecConnection
{
public:
    MOCK_METHOD1(Init, DLL_INT(short));
};

#endif

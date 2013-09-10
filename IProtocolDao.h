#ifndef IPROTOCOLDAO_H
#define IPROTOCOLDAO_H

#include "Protocol.h"

class IProtocolDao
{
public:
    virtual Protocol loadProtocol() = 0;
};

#endif // IPROTOCOLDAO_H

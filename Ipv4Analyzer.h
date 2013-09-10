#ifndef IPV4ANALYZER_H
#define IPV4ANALYZER_H

#include "DataAnalyzer.h"
#include "IProtocolDao.h"
#include "ProtocolDaoXml.h"
#include "Protocol.h"
#include "DefaultDataConverter.h"

class Ipv4Analyzer : public DataAnalyzer //TODO remove this mock class
{
private:
    IProtocolDao* pDao;
    DefaultDataConverter ddc;
    Protocol proto;
public:
    Ipv4Analyzer();

    int analyze(PacketContext packetContext);
};

#endif // IPV4ANALYZER_H

#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H

#include "Packet.h"
#include <QByteArray>
#include <QHash>

class PacketFactory
{
private:
    QHash<quint64, Packet*> m_packetPool;

public:
    Packet* getPacket (const QByteArray* packetContext);
};

#endif // PACKETFACTORY_H


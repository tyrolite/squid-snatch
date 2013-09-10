#ifndef PACKET_H
#define PACKET_H

#include "Protocol.h"

#include <QtGlobal>
#include <QString>
#include <QByteArray>
#include <QMap>
#include <QList>

class Packet
{
private:
    QList<Protocol*> m_protocols;

public:
    QList<Protocol*> getProtocols ();

    QMap<qint32, Field*> getFAFields ();

    qint32 setFAFields (const QMap<qint32, QString>& newFAFields);

    Field* getField (const QString& fieldName);
};

#endif // PACKET_H

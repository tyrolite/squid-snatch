#include "DefaultDataConverter.h"
#include <QVariant>
#include <QTextStream>
#include <arpa/inet.h>
#include <netinet/ip.h>		    // for IP header
#include <netinet/if_ether.h>	    // for Ethernet header


DefaultDataConverter::DefaultDataConverter(AbstractDataConverter *parent):
        AbstractDataConverter(parent)
{
}

QString DefaultDataConverter::toQuint16(const QByteArray& bytes) const// TODO add exception
{
    quint16 ret;
    memcpy(&ret, bytes.constData(), sizeof(quint16));
    ret = ntohs(ret);
    return QVariant(ret).toString();
}

QByteArray DefaultDataConverter::fromQuint16(const QString& str) const
{
    quint16 ret;
    QString strCpy = str;
    QTextStream ts(&strCpy, QIODevice::ReadOnly);
    ts>>ret;
    ret = htons(ret);
    return QByteArray((const char*)&ret, sizeof(quint16));
}

QString DefaultDataConverter::toIpv4(const QByteArray& bytes) const// TODO add exception
{
    struct in_addr* a_ptr = (struct in_addr*)bytes.constData();
    char buff[64];

    //a_ptr->s_addr = ntohl(a_ptr->s_addr);
    sprintf(buff, "%s", inet_ntoa(*a_ptr));
    return QString(buff);
}

QByteArray DefaultDataConverter::fromIpv4(const QString& str) const
{
    // TODO
    str.toAscii();
    return QByteArray();
}

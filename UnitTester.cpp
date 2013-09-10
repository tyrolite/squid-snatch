#include "UnitTester.h"
#include "IProtocolDao.h"
#include "ProtocolDaoXml.h"
#include "DefaultDataConverter.h"
#include "PacketListener.h"
#include "DataAnalyzer.h"
#include "Ipv4Analyzer.h"

#include <QDebug>

UnitTester::UnitTester()
{
}

void UnitTester::testProtocolDao()
{
    IProtocolDao* ipd = new ProtocolDaoXml("../SquidSnatch/ipv4.xml");
    Protocol p = ipd->loadProtocol();
    qDebug("done.");
}

void UnitTester::testDirectConversion()
{
    DefaultDataConverter ddc;

    quint16 port = 8080;
    QByteArray ba((const char*)&port, sizeof(quint16));
    qDebug()<< ddc.toQuint16(ba);

    QString strPort = "1089";      // 1024 + 65
    ba = ddc.fromQuint16(strPort);
    qDebug()<< ba;
}

void UnitTester::testIndirectConversion()
{
    DefaultDataConverter ddc;

    quint16 port = 8080;
    QByteArray ba((const char*)&port, sizeof(quint16));
    qDebug()<< ddc.toString("toQuint16", ba);

    QString strPort = "65";      // 1024 + 65
    ba = ddc.fromString("fromQuint16", strPort);
    qDebug()<< ba;
}

void UnitTester::testPS()
{
    /*PacketListener pl;
    pl.addAnalyzer(new Ipv4Analyzer());
    pl.start();*/
}

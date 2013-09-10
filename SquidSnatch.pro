#-------------------------------------------------
#
# Project created by QtCreator 2011-05-08T15:02:53
#
#-------------------------------------------------

QT       += core gui xml

TARGET = SquidSnatch
TEMPLATE = app

LIBS = -lpcap

SOURCES += main.cpp\
    ProtocolDaoXml.cpp \
    Field.cpp \
    UnitTester.cpp \
    AbstractDataConverter.cpp \
    DefaultDataConverter.cpp \
    PacketListnener.cpp \
    DataAnalyzer.cpp \
    Ipv4Analyzer.cpp \
    MainWin.cpp \
    MainCtrl.cpp \
    PacketContext.cpp \
    CapturedTableModel.cpp

HEADERS  += MainWin.h \
    Protocol.h \
    PacketListener.h \
    PacketFactory.h \
    Packet.h \
    Field.h \
    DataAnalyzer.h \
    IProtocolDao.h \
    ProtocolDaoXml.h \
    UnitTester.h \
    AbstractDataConverter.h \
    DefaultDataConverter.h \
    Ipv4Analyzer.h \
    MainCtrl.h \
    PacketContext.h \
    CapturedTableModel.h

FORMS    += \
    MainWin.ui

OTHER_FILES += \
    resource/stop.png \
    resource/start.png \
    resource/sniff.png \
    resource/pack_gen.png \
    resource/net_mon.png \
    resource/ipv4.xml

#ifndef PACKETLISTENER_H
#define PACKETLISTENER_H

#include "DataAnalyzer.h"
#include <QThread>
#include <QList>
#include <pcap/pcap.h>

#define BUFF_SIZE 256
#define MAX_PACK_COUNT 256
#define PCAP_ERR(x) ((x<0)&&(-2 != x))

class MainCtrl;

class PacketListener: public QThread
{
    Q_OBJECT
private:
    char m_device[BUFF_SIZE];
    char m_filter[BUFF_SIZE];
    char m_errBuf[PCAP_ERRBUF_SIZE];
    char m_errBuf2[PCAP_ERRBUF_SIZE];
    bool m_prom;
    pcap_t* m_sHandle;
    MainCtrl* m_mainCtrl;
    QList<DataAnalyzer*> m_analyzers;

protected:
    void run();

public:
    PacketListener(MainCtrl* mainCtrl);
    ~PacketListener();

    void setDevice(const QString& device);

    void setFilter(const QString& filter);

    void setPromisc(bool prom);

    void addAnalyzer(DataAnalyzer* analyzer);

    void breakloop();

    QList<DataAnalyzer*>* getAnalyzers();

};

#endif // PACKETLISTENER_H


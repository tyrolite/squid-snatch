#include "PacketListener.h"

#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip.h>		    // for IP header
#include <netinet/if_ether.h>	    // for Ethernet header
#include <MainCtrl.h>

void _packetHandler(u_char *userdata, const struct pcap_pkthdr *pkthdr,
                const u_char *pkt);

PacketListener::PacketListener(MainCtrl* mainCtrl):
        QThread(mainCtrl),
        m_mainCtrl(mainCtrl),
        m_sHandle(NULL)
{

}

PacketListener::~PacketListener()
{
    // close session
    if(NULL != m_sHandle)
    {
        pcap_close(m_sHandle);
        m_sHandle = NULL;
    }
}

void PacketListener::setDevice(const QString& device)
{
    strcpy(m_device, device.toAscii().constData());
}

void PacketListener::setFilter(const QString& filter)
{
    strcpy(m_filter, filter.toAscii().constData());
}

void PacketListener::setPromisc(bool prom)
{
    m_prom = prom;
}

void PacketListener::addAnalyzer(DataAnalyzer* analyzer)
{
    m_analyzers.append(analyzer);
}

void PacketListener::breakloop()
{
    pcap_breakloop(m_sHandle);
    if(NULL != m_sHandle)
    {
        pcap_close(m_sHandle);
        m_sHandle = NULL;
    }
    m_mainCtrl->log("session stopped.");
}

QList<DataAnalyzer*>* PacketListener::getAnalyzers()
{
    return &m_analyzers;
}

void PacketListener::run()
{
    m_mainCtrl->log("starting session ...");

    bpf_u_int32 ip_addr; // ip of device
    bpf_u_int32 netmask; // netmask of device
    struct bpf_program cfilter; //compiled filter
    int rc;

    sprintf(m_errBuf, "Device: %s",m_device);
    m_mainCtrl->log(m_errBuf);

    int promisc = 0;
    if(m_prom)
        promisc = 1;

    // open a session
    m_sHandle = pcap_open_live(m_device, BUFSIZ, promisc, 10000, m_errBuf); //TODO move to start
    if(m_sHandle == NULL)
    {
        sprintf(m_errBuf2, "Could not open device %s: %s", m_device, m_errBuf);
        m_mainCtrl->log(m_errBuf2);
        return;
    }

    rc = pcap_setnonblock(m_sHandle, 1, m_errBuf);
    if(PCAP_ERR(rc))
    {
        sprintf(m_errBuf2, "Unable to set session to non-blocking mode !");
        m_mainCtrl->log(m_errBuf2);
        return;
    }

    // get ip and netmask for device
    rc = pcap_lookupnet(m_device, &ip_addr, &netmask, m_errBuf);
    if(PCAP_ERR(rc))
    {
        sprintf(m_errBuf2, "Can't get ip and netmask for devive:%s", m_device);
        m_mainCtrl->log(m_errBuf2);
        ip_addr = 0;
        netmask = 0;
    }

    // compile filter
    rc = pcap_compile(m_sHandle, &cfilter, m_filter, 0, netmask);
    if(PCAP_ERR(rc))
    {
        sprintf(m_errBuf, "Invalid filter!");
        m_mainCtrl->log(m_errBuf);
        return;
    }

    // set filter to session
    rc = pcap_setfilter(m_sHandle, &cfilter);
    if(PCAP_ERR(rc))
    {
        sprintf(m_errBuf, "Cannot set filter to session!");
        m_mainCtrl->log(m_errBuf);
        return;
    }

    // start sniffing loop
    rc = pcap_loop(m_sHandle, MAX_PACK_COUNT, _packetHandler, (u_char*)this);
    if(PCAP_ERR(rc))
    {
        sprintf(m_errBuf, "Loop error: %d", rc);
        m_mainCtrl->log(m_errBuf);
        return;
    }

}

void _packetHandler(u_char *userdata, const struct pcap_pkthdr *pkthdr,
                const u_char *pkt)
{
        printf("Got a packet with len:%d!\n", pkthdr->caplen);
        fflush(stdout);
        PacketContext pc(pkthdr, pkt);

        PacketListener* pl = (PacketListener*) userdata;
        QList<DataAnalyzer*>* analyzers = pl->getAnalyzers();

        for(int i = 0; i < analyzers->length(); i++)
        {
            analyzers->at(i)->analyze(pc);//TODO performance replace pack context with 2 params
        }
}

#ifndef PACKETCONTEXT_H
#define PACKETCONTEXT_H

#include <pcap/pcap.h>

#define MAX_PACK_SIZE 65535

class PacketContext
{
private:
    struct pcap_pkthdr m_packetHeader;
    u_char m_packetData[MAX_PACK_SIZE];

public:
    PacketContext(const struct pcap_pkthdr* m_packetHeader, const u_char* m_packetData);

    const struct pcap_pkthdr* getPacketHeader() const;

    const u_char* getPacketData() const;
};

#endif // PACKETCONTEXT_H

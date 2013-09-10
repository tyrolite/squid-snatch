#include "PacketContext.h"
#include <string.h>

PacketContext::PacketContext(const struct pcap_pkthdr* packetHeader, const u_char* packetData)
{
    memcpy(&m_packetHeader, packetHeader, sizeof(struct pcap_pkthdr));
    memcpy(m_packetData, packetData, packetHeader->caplen);
    //m_packetData = packetData;
}

const struct pcap_pkthdr* PacketContext::getPacketHeader() const
{
    return &m_packetHeader;
}

const u_char* PacketContext::getPacketData() const
{
    return m_packetData;
}

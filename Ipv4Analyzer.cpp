#include "Ipv4Analyzer.h"

#include <arpa/inet.h>
#include <netinet/ip.h>		    // for IP header
#include <netinet/if_ether.h>	    // for Ethernet header

#include <stdio.h>

Ipv4Analyzer::Ipv4Analyzer()
{
    pDao = new ProtocolDaoXml("../SquidSnatch/ipv4.xml");
    proto = pDao->loadProtocol();
}

int Ipv4Analyzer::analyze(PacketContext packetContext)
{
    const char* data = (const char*)packetContext.getPacketData();
    QByteArray all(data);

    struct iphdr *iph;
    struct in_addr addr_1, addr_2;

    iph = (struct iphdr*) data;
    addr_1.s_addr = iph->saddr;
    addr_2.s_addr = iph->daddr;

    printf("IPv4|");
    printf("Source: %s \t", inet_ntoa(addr_1));
    printf("Destionation: %s \n", inet_ntoa(addr_2));

    Field f1 = proto.getSubFields().at(4); //TotalLength
    Field f2 = proto.getSubFields().at(5); //Identification

    QByteArray ba(data);


    QByteArray ff1(data+ (f1.getOffset()/8), (f1.getLength()/8));
    printf("ff1 :%x %x\n", ff1.at(0), ff1.at(1));
    QByteArray ff2(data+ (f2.getOffset()/8), (f2.getLength()/8));
    printf("ff2 :%x %x\n", ff2.at(0), ff2.at(1));

    QString sf1 = ddc.toQuint16(ff1);
    QString sf2 = ddc.toQuint16(ff2);

    printf("IPv4|");
    printf("TotalLength: %s \t", sf1.toAscii().constData());
    printf("Identification: %s \n\n", sf2.toAscii().constData());

    fflush(stdout);

    return 0;
}

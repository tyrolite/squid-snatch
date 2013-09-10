#include "CapturedTableModel.h"
#include <netinet/if_ether.h>	    // for Ethernet header
#include <netinet/ip.h>		    // for IP header
#include <netinet/tcp.h>
#include <netinet/udp.h>



CapturedTableModel::CapturedTableModel(QObject* parent):
        QAbstractItemModel(parent)
{
    m_columnNames.append("Timestamp");
    m_columnNames.append("Source");
    m_columnNames.append("Destination");
    m_columnNames.append("Protocol");
}

int CapturedTableModel::columnCount( const QModelIndex & parent) const
{
    return m_columnNames.size();
}

QVariant CapturedTableModel::headerData ( int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if((orientation ==  Qt::Horizontal))
            return m_columnNames.at(section);
        else
            return QVariant(section);
    }
    else
    {
        return QVariant();
    }
}

QVariant CapturedTableModel::data( const QModelIndex & index, int role) const
{
    if((index.row() < m_contextList.size()) && (role == Qt::DisplayRole))
    {
        //m_mtx.lock();
        PacketContext pc = m_contextList.at(index.row());
        //m_mtx.unlock();

        if(index.column() == COLUMN_TIMESTAMP)
        {
            struct timeval tv;
            time_t nowtime;
            struct tm *nowtm;
            char tmbuf[64], buf[64];


            tv = pc.getPacketHeader()->ts;
            nowtime = tv.tv_sec;
            nowtm = localtime(&nowtime);
            strftime(tmbuf, sizeof tmbuf, "%H:%M:%S", nowtm);
            snprintf(buf, sizeof buf, "%s.%03d", tmbuf, (tv.tv_usec)/1000);
            return QVariant(buf);

        }
        else if((index.column() == COLUMN_SOURCE) || (index.column() == COLUMN_DESTINATION))
        {
            const char *buff = (const char*) pc.getPacketData();
            buff = buff + sizeof(struct ether_header);	// jump over Ethernet header

            struct iphdr *iph;
            struct in_addr addr;
            iph = (struct iphdr *) buff;

            if(index.column() == COLUMN_SOURCE)
            {
                addr.s_addr = iph->saddr;
                return ddc.toIpv4(QByteArray((const char*)&addr, sizeof(struct in_addr)));
            }
            else
            {
                addr.s_addr = iph->daddr;
                return ddc.toIpv4(QByteArray((const char*)&addr, sizeof(struct in_addr)));
            }
        }
        else if(index.column() == COLUMN_PROTOCOL)
        {
            const char *buff = (const char*) pc.getPacketData();
            buff = buff + sizeof(struct ether_header);	// jump over Ethernet header

            struct iphdr *iph;
            struct in_addr addr;
            iph = (struct iphdr *) buff;

            buff = buff + iph->ihl;
            if(iph->protocol == IPPROTO_TCP)
            {
                struct tcphdr* tcph = (struct tcphdr*)buff;
                if(tcph->dest == 80 || tcph->dest == 8080)
                    return "HTTP";
                else  if(tcph->dest == 5050)
                    return "YMSG";
                else
                    return "TCP";
            }
            else if(iph->protocol == IPPROTO_UDP)
            {
                return "UDP";
            }
            else
            {
                return "TODO";
            }
        }
        else
            return m_columnNames.at(index.column()); //TODO get data from packet and context
    }
    else
    {
        return QVariant();
    }
}

QModelIndex CapturedTableModel::index( int row, int column, const QModelIndex & parent) const
{
    return QAbstractItemModel::createIndex(row, column);
}

QModelIndex CapturedTableModel::parent( const QModelIndex & index ) const
{
    return QModelIndex();
}

int CapturedTableModel::rowCount(const QModelIndex& parent) const
{
    //m_mtx.lock();
    int ret = m_contextList.size();
    //m_mtx.unlock();

    return ret;
}

int CapturedTableModel::analyze(PacketContext packetContext)
{
    m_mtx.lock();
    beginInsertRows(QModelIndex(), m_contextList.size()-1, m_contextList.size() );

    m_contextList.append(packetContext);

    endInsertRows();
    m_mtx.unlock();

    return 0;
}

PacketContext CapturedTableModel::contextAt(int index)
{
    return m_contextList.at(index);
}

void CapturedTableModel::clear()
{
    beginResetModel();
    m_contextList.clear();
    endResetModel();
}

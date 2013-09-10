#include "MainCtrl.h"
#include <QDebug>
#include <QStringList>
#include <ProtocolDaoXml.h>
#include <arpa/inet.h>

MainCtrl::MainCtrl(QObject *parent) :
    QObject(parent),
    m_packetListener(this)
{
    connect(this, SIGNAL(logged(QString)), &m_mainWin, SLOT(log(QString)));
    connect(m_mainWin.getStartBtn(), SIGNAL(pressed()), this, SLOT(start()));
    connect(m_mainWin.getStopBtn(), SIGNAL(pressed()), this, SLOT(stop()));
    connect(m_mainWin.getCapturedTv(), SIGNAL(clicked(QModelIndex)), this, SLOT(updateTextTe(QModelIndex)));

    m_packetListener.addAnalyzer(&m_capturedTableModel);
    m_mainWin.getCapturedTv()->setModel(&m_capturedTableModel);
    m_ipv4Dao = new ProtocolDaoXml("resource/ipv4.xml");

    QStringList treeHeader;
    treeHeader.append("Name");
    treeHeader.append("Description");
    m_mainWin.getFieldsTw()->setHeaderLabels(treeHeader);
    addProtocolItem(m_mainWin.getFieldsTw(), m_ipv4Dao);

    QImage netMonImg;
    netMonImg.load("resource/net_mon_pic.png");
    m_mainWin.getImgLabel()->setPixmap(QPixmap::fromImage(netMonImg));
}

void MainCtrl::begin()
{
    m_mainWin.show();
}

void MainCtrl::start()
{
    m_capturedTableModel.clear();
    m_packetListener.setDevice(m_mainWin.getInterface());
    m_packetListener.setFilter(m_mainWin.getFilter());
    m_packetListener.setPromisc(m_mainWin.getPromisc());
    m_packetListener.start();

}

void MainCtrl::stop()
{
    m_packetListener.breakloop();
    m_packetListener.quit();
}

void MainCtrl::log(const QString& msg)
{
    emit logged(msg);
}

void MainCtrl::updateTextTe(const QModelIndex& clickedIndex)
{
    qDebug()<<"selection changed!\n";
    int row = clickedIndex.row();
    if(row >= 0 && row < m_capturedTableModel.rowCount())
    {
        PacketContext pc = m_capturedTableModel.contextAt(row);
        qint32 len = pc.getPacketHeader()->caplen;
        QByteArray ba((const char*)pc.getPacketData(), len);
        for(int i = 0; i < ba.size()-1; i++)
            if((int)ba[i] < 32) // non-printable
            {
                ba[i] = '-';
            }
        m_mainWin.getTextTe()->setPlainText(ba);
    }
}

void MainCtrl::addProtocolItem(QTreeWidget* treeWid, IProtocolDao* protoDao)
{
    Protocol proto = protoDao->loadProtocol();

    QTreeWidgetItem* rootItem = new QTreeWidgetItem(treeWid);
    rootItem->setText(0, proto.getName());

    buildItemDfs(&proto, rootItem);
}

void MainCtrl::buildItemDfs(Field* field, QTreeWidgetItem *parentItem)
{
    if(field->isLeaf())
    {
        return;
    }
    else
    {
        for(int i = 0; i < field->getSubFields().size(); ++i)
        {
            Field memField = field->getSubFields().at(i);

            QTreeWidgetItem* treeItem = new QTreeWidgetItem(parentItem);
            treeItem->setText(0, memField.getName());
            treeItem->setText(1, memField.getDescription());
        }
    }

}

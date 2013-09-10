#ifndef MAINCTRL_H
#define MAINCTRL_H

#include <QObject>
#include <MainWin.h>
#include <PacketListener.h>

#include <CapturedTableModel.h>
#include <QTreeWidgetItem>

#include <IProtocolDao.h>

class MainCtrl : public QObject
{
private:
    Q_OBJECT
    MainWin m_mainWin;
    PacketListener m_packetListener;
    IProtocolDao* m_ipv4Dao;

    /* Sniffer */
    CapturedTableModel m_capturedTableModel;

    /* Plots */

public:
    explicit MainCtrl(QObject *parent = 0);

    void begin();

signals:
    void logged(const QString& msg);

public slots:
    void start();
    void stop();
    void log(const QString& msg);
    void updateTextTe(const QModelIndex& clickedIndex);

private:
    void addProtocolItem(QTreeWidget* treeWid, IProtocolDao* protoDao);
    void buildItemDfs(Field* field, QTreeWidgetItem *parentItem);

};

#endif // MAINCTRL_H

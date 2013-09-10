#ifndef CAPTUREDTABLEMODEL_H
#define CAPTUREDTABLEMODEL_H

#include <QAbstractItemModel>
#include <DataAnalyzer.h>
#include <QList>
#include <PacketContext.h>
#include <DefaultDataConverter.h>
#include <QMutex>

class CapturedTableModel : public QAbstractItemModel, public DataAnalyzer
{
    Q_OBJECT
private:
    QList<PacketContext> m_contextList;
    QMutex m_mtx;

    QList<QString> m_columnNames;
    DefaultDataConverter ddc;

public:
    static const int COLUMN_TIMESTAMP = 0;
    static const int COLUMN_SOURCE = 1;
    static const int COLUMN_DESTINATION = 2;
    static const int COLUMN_PROTOCOL = 3;

    explicit CapturedTableModel(QObject* parent = 0);

    /* QAbstractItemModel */
    int columnCount (const QModelIndex & parent = QModelIndex()) const;

    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;

    QModelIndex index (int row, int column, const QModelIndex & parent = QModelIndex()) const;

    QModelIndex parent (const QModelIndex & index) const;

    int rowCount (const QModelIndex & parent = QModelIndex()) const;

    /* other */
    PacketContext contextAt(int index);

    /* DataAnalyzer */
    int analyze(PacketContext packetContext);

    void clear();
};

#endif // CAPTUREDTABLEMODEL_H

#ifndef DATAANALYZER_H
#define DATAANALYZER_H

#include "AbstractDataConverter.h"
#include "PacketContext.h"

#include <QMap>

class DataAnalyzer
{
private:
    QMap<quint32, AbstractDataConverter*> m_converters;

public:
    void addConverter(AbstractDataConverter* converter);
    qint32 removeConverter(qint32 id);

    virtual int analyze(PacketContext packetContext) = 0;
};

#endif // DATAANALYZER_H

#include "DataAnalyzer.h"

void DataAnalyzer::addConverter(AbstractDataConverter* converter)
{
    m_converters.insert(converter->getId(), converter);
}

qint32 DataAnalyzer::removeConverter(qint32 id)
{
    m_converters.remove(id);
    return 0;
}

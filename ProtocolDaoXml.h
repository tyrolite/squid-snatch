#ifndef PROTOCOLDAOXML_H
#define PROTOCOLDAOXML_H

#include "Protocol.h"
#include "IProtocolDao.h"

#include <QString>
#include <QDomDocument>
#include <QFile>

class ProtocolDaoXml : public IProtocolDao
{
private:
    QDomDocument m_doc;
    QFile m_file;
    QDomElement m_docElem;

public:
    ProtocolDaoXml(const QString& filename);

    Protocol loadProtocol();

private:
    void domDfsTraversal(QDomElement* domNode, Field* protoField);
};

#endif // PROTOCOLDAOXML_H

#include "ProtocolDaoXml.h"
#include <QDebug>

ProtocolDaoXml::ProtocolDaoXml(const QString& filename):
        m_doc("protocol"),
        m_file(filename)
{
     if (!m_file.open(QIODevice::ReadOnly))
         return;
     if (!m_doc.setContent(&m_file)) {
         m_file.close();
         return;
     }
     m_file.close();

     m_docElem = m_doc.documentElement();
}

Protocol ProtocolDaoXml::loadProtocol()
{
    Protocol cProtocol;
    QString attr;

    domDfsTraversal(&m_docElem, &cProtocol);
    attr = m_docElem.attribute("name");
    cProtocol.setName(attr);
    if(cProtocol.getSubFields().size() > 0)
        cProtocol.setIsLeaf(false);

    return cProtocol;
}

void ProtocolDaoXml::domDfsTraversal(QDomElement* domElem, Field* protoField)
{
    QDomNodeList cLevelNodes = domElem->childNodes(); //current level nodes
    QString attr;
    bool ok;

    for(size_t i = 0; i < cLevelNodes.count(); ++i)
        if(cLevelNodes.at(i).isElement())
        {
            QDomElement elem = cLevelNodes.at(i).toElement();


            Field cField;
            domDfsTraversal(&elem, &cField);

            attr = elem.attribute("name");
            cField.setName(attr);
            //qDebug()<<cField.getName();

            attr = elem.attribute("offset");
            cField.setOffset(attr.toInt(&ok));

            attr = elem.attribute("length");
            cField.setLength(attr.toInt(&ok));

            attr = elem.attribute("type");
            cField.setType(attr);

            if(elem.hasAttribute("descr"))
            {
                attr = elem.attribute("descr");
                cField.setDescription(attr);
            }

            if(cField.getSubFields().length() == 0)
                cField.setIsLeaf(true);

            protoField->addSubField(cField);
        }
}

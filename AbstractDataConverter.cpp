#include "AbstractDataConverter.h"
#include <QString>

AbstractDataConverter::AbstractDataConverter(QObject *parent) :
    QObject(parent)
{

}

quint32 AbstractDataConverter::getId ()
{
    return m_id;
}

void AbstractDataConverter::setId(quint32 id)
{
    m_id = id;
}

QString AbstractDataConverter::toString (const QString& converterMethod,
                                         const QByteArray& bytes)
{
    QString ret;
    bool rc;

    rc = QMetaObject::invokeMethod(this,
                             converterMethod.toAscii().constData(),
                             Q_RETURN_ARG(QString, ret),
                             Q_ARG(QByteArray, bytes));
    return ret;
}

QByteArray AbstractDataConverter::fromString (const QString& converterMethod,
                                              const QString& str)
{
    QByteArray ret;
    bool rc;

    rc = QMetaObject::invokeMethod(this,
                             converterMethod.toAscii().constData(),
                             Q_RETURN_ARG(QByteArray, ret),
                             Q_ARG(const QString&, str));
    return ret;
}

#ifndef ABSTRACTDATACONVERTER_H
#define ABSTRACTDATACONVERTER_H

#include <QObject>
#include <QString>
#include <QByteArray>

class AbstractDataConverter : public QObject
{
private:
    Q_OBJECT
    quint32 m_id;

public:
    explicit AbstractDataConverter(QObject *parent = 0);

    quint32 getId();
    void setId(quint32 id);

signals:

public slots:
    /**
      * Convert the binary representation of data from bytes to a printable QString using
      * the specified converterMethod
      */
    QString toString(const QString& converterMethod, const QByteArray& bytes); // TODO throw exception for conversion

    /**
      * Convert the QString value to the binary representation of data using the specified
      * converterMethod
      */
    QByteArray fromString(const QString& converterMethod, const QString& str);
};

#endif // ABSTRACTDATACONVERTER_H

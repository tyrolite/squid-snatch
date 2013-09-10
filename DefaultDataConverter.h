#ifndef DEFAULTDATACONVERTER_H
#define DEFAULTDATACONVERTER_H

#include <AbstractDataConverter.h>
#include <QObject>
#include <QString>
#include <QByteArray>

class DefaultDataConverter : public AbstractDataConverter
{
private:
    Q_OBJECT

public:
    explicit DefaultDataConverter(AbstractDataConverter *parent = 0);

signals:

public slots:
    /**
      * Convert binary to QString
      */
    QString toQuint16(const QByteArray& bytes) const; // TODO add exception

    /**
      * Convert QString to binary
      */
    QByteArray fromQuint16(const QString& str) const;

    /**
      * Convert binary to Ipv4
      */
    QString toIpv4(const QByteArray& bytes) const; // TODO add exception

    /**
      * Convert Ipv4 to binary
      */
    QByteArray fromIpv4(const QString& str) const;
};

#endif // DEFAULTDATACONVERTER_H

#ifndef FIELD_H
#define FIELD_H

#include <QtGlobal>
#include <QString>
#include <QList>

class Field {

private:
    qint32 m_id;
    QString m_name;
    qint32 m_offset;
    qint32 m_length;
    QString m_type;
    bool m_isLeaf;
    QString m_description;
    QList<Field> m_subFields;

public:

    qint32 getId() const;
    void setId(qint32 id);

    bool isLeaf() const;
    void setIsLeaf(bool isLeaf);

    qint32 getLength() const;
    void setLength(qint32 length);

    const QString& getName() const;
    void setName(const QString& name);

    qint32 getOffset() const;
    void setOffset(qint32 offset);

    const QString& getType() const;
    void setType(const QString& type);

    const QString& getDescription() const;
    void setDescription(const QString& description);

    const QList<Field>& getSubFields() const;
    void setSubFields(const QList<Field>& subFields);
    void addSubField(const Field& newSubField);

};

#endif // FIELD_H

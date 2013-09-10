#include "Field.h"

qint32 Field::getId() const
{
    return m_id;
}

void Field::setId(qint32 id)
{
    m_id = id;
}

bool Field::isLeaf() const
{
    return m_isLeaf;
}

void Field::setIsLeaf(bool isLeaf)
{
    m_isLeaf = isLeaf;
}

qint32 Field::getLength() const
{
    return m_length;
}

void Field::setLength(qint32 length)
{
    m_length = length;
}

const QString& Field::getName() const
{
    return m_name;
}

void Field::setName(const QString& name)
{
    m_name = name;
}

qint32 Field::getOffset() const
{
    return m_offset;
}

void Field::setOffset(qint32 offset)
{
    m_offset = offset;
}

const QString& Field::getType() const
{
    return m_type;
}
void Field::setType(const QString& type)
{
    m_type = type;
}

const QString& Field::getDescription() const
{
    return m_description;
}
void Field::setDescription(const QString& description)
{
    m_description = description;
}

const QList<Field>& Field::getSubFields() const
{
    return m_subFields;
}

void Field::setSubFields(const QList<Field>& subFields)
{
    m_subFields = subFields;
}

void Field::addSubField(const Field& newSubField)
{
    m_subFields.append(newSubField);
}

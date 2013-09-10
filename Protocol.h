#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "Field.h"

#include <QtGlobal>
#include <QList>

/// class Protocol - 
class Protocol : public Field {

private:
    quint64 m_hashKey;
};

#endif // PROTOCOL_H


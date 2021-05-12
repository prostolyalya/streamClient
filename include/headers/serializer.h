#ifndef SERIALIZER_H
#define SERIALIZER_H
#pragma once
#include <QStringList>

namespace Serialize {
    QString serialize(QStringList data);
    QStringList deserialize(QString data);
}

#endif // SERIALIZER_H

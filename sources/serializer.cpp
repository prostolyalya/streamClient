#include "serializer.h"

QString Serialize::serialize(QStringList data)
{
    QString res = "";
    for(const auto& tmp : data)
    {
        res += QString::number(tmp.size()) + "/" + tmp;
    }
    return res;
}

QStringList Serialize::deserialize(QString data)
{
    QStringList list;
    while(!data.isEmpty())
    {
        int pos = data.indexOf("/");
        if (pos == -1)
            return list;
        int size = data.midRef(0, pos).toInt();
        QString name = data.mid(pos + 1, size);
        list.append(name);
        data.remove(0, pos + size + 1);
    }
    return list;
}

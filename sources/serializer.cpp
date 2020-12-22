#include "serializer.h"

void Serialize::serializeMessage(QByteArray &data)
{
    int size = data.size();
    QByteArray data_size = QByteArray::number(size);
    if(QByteArray::number(size).size() == 1)
    {
        data_size.push_front("0");
    }
    data = data_size + data;
}

#include "cryptor.h"

void Cryptor::encryptDecrypt(const std::string &key, std::vector<char> data)
{
    for (size_t i = 0; i != data.size(); i++)
        data[i] ^= key[ i % key.size() ];
}

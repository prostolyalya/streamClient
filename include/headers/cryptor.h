#ifndef CRYPTOR_H
#define CRYPTOR_H
#pragma once

#include <QString>
namespace Cryptor {
    void encryptDecrypt (const std::string &key, std::vector<char> data);
}

#endif // CRYPTOR_H

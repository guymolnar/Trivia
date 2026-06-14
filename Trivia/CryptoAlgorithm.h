#pragma once
#include <string>

class CryptoAlgorithm {
public:
    virtual ~CryptoAlgorithm() = default;
    virtual std::string encrypt(std::string message) = 0;
    virtual std::string decrypt(std::string cypher) = 0;
};
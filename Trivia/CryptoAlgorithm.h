#pragma once
#include <vector>
#include <cstdint>

class CryptoAlgorithm {
public:
    virtual ~CryptoAlgorithm() = default;
    virtual std::vector<uint8_t> encrypt(std::vector<uint8_t> message) = 0;
    virtual std::vector<uint8_t> decrypt(std::vector<uint8_t> cypher) = 0;
};
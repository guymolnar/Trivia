#pragma once
#include "CryptoAlgorithm.h"

class OTPCryptoAlgorithm : public CryptoAlgorithm {
public:
    OTPCryptoAlgorithm(const std::vector<uint8_t>& key);
    std::vector<uint8_t> encrypt(std::vector<uint8_t> message) override;
    std::vector<uint8_t> decrypt(std::vector<uint8_t> cypher) override;
private:
    std::vector<uint8_t> m_key;  
};
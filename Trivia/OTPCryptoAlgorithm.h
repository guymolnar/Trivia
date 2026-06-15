#pragma once
#pragma once
#include "CryptoAlgorithm.h"

class OTPCryptoAlgorithm : public CryptoAlgorithm {
public:
    OTPCryptoAlgorithm(const std::string& key);
    std::string encrypt(std::string message) override;
    std::string decrypt(std::string cypher) override;
private:
    std::string m_key;
};
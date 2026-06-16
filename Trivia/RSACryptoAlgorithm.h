#pragma once
#include "CryptoAlgorithm.h"
#include <cryptopp/rsa.h>

class RSACryptoAlgorithm : public CryptoAlgorithm {
public:
    RSACryptoAlgorithm();
    std::vector<uint8_t> encrypt(std::vector<uint8_t> message) override;
    std::vector<uint8_t> decrypt(std::vector<uint8_t> cypher) override;
private:
    CryptoPP::RSA::PublicKey  m_publicKey;
    CryptoPP::RSA::PrivateKey m_privateKey;
};
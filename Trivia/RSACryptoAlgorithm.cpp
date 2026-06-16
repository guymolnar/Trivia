#include "RSACryptoAlgorithm.h"
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>
#include <stdexcept>

RSACryptoAlgorithm::RSACryptoAlgorithm()
{
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 2048);  
    m_privateKey = CryptoPP::RSA::PrivateKey(params);
    m_publicKey = CryptoPP::RSA::PublicKey(params);
}

std::vector<uint8_t> RSACryptoAlgorithm::encrypt(std::vector<uint8_t> message)
{
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Encryptor enc(m_publicKey);

    std::string cipher;
    CryptoPP::StringSource ss(message.data(), message.size(), true, new CryptoPP::PK_EncryptorFilter(rng, enc, new CryptoPP::StringSink(cipher)));
    return std::vector<uint8_t>(cipher.begin(), cipher.end());
}
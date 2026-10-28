#include "AESCryptoAlgorithm.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <stdexcept>

AESCryptoAlgorithm::AESCryptoAlgorithm(const std::vector<uint8_t>& key) : m_key(key)
{
}

std::vector<uint8_t> AESCryptoAlgorithm::encrypt(std::vector<uint8_t> message)
{
    CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption enc;
    enc.SetKey(m_key.data(), m_key.size());

    std::string cipher;
    CryptoPP::StringSource ss(message.data(), message.size(), true, new CryptoPP::StreamTransformationFilter(enc, new CryptoPP::StringSink(cipher)));

    return std::vector<uint8_t>(cipher.begin(), cipher.end());
}

std::vector<uint8_t> AESCryptoAlgorithm::decrypt(std::vector<uint8_t> cypher)
{
    CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption dec;
    dec.SetKey(m_key.data(), m_key.size());

    std::string recovered;
    CryptoPP::StringSource ss(cypher.data(), cypher.size(), true, new CryptoPP::StreamTransformationFilter(dec, new CryptoPP::StringSink(recovered)));

    return std::vector<uint8_t>(recovered.begin(), recovered.end());
}
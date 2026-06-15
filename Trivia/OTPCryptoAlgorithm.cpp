#include "OTPCryptoAlgorithm.h"

OTPCryptoAlgorithm::OTPCryptoAlgorithm(const std::vector<uint8_t>& key) : m_key(key)
{

}

std::vector<uint8_t> OTPCryptoAlgorithm::encrypt(std::vector<uint8_t> message)
{
    for (size_t i = 0; i < message.size(); i++)
    {
        message[i] ^= m_key[i % m_key.size()];   //xoring each byte
    }
    return message;
}
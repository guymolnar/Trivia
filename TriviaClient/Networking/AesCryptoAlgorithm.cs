using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;

namespace TriviaClient.Networking
{
    public class AesCryptoAlgorithm : ICryptoAlgorithm
    {
        private byte[] _key;
        public AesCryptoAlgorithm(byte[] key) { _key = key; }

        public byte[] Encrypt(byte[] message)
        {
            using var aes = Aes.Create();
            aes.Key = _key;
            aes.Mode = CipherMode.ECB;
            aes.Padding = PaddingMode.PKCS7;
            using var enc = aes.CreateEncryptor();
            return enc.TransformFinalBlock(message, 0, message.Length);
        }

        public byte[] Decrypt(byte[] cypher)
        {
            using var aes = Aes.Create();
            aes.Key = _key;
            aes.Mode = CipherMode.ECB;
            aes.Padding = PaddingMode.PKCS7;
            using var dec = aes.CreateDecryptor();
            return dec.TransformFinalBlock(cypher, 0, cypher.Length);
        }
    }
}

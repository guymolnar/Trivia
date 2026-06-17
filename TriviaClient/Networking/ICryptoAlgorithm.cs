using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Networking
{
    public interface ICryptoAlgorithm
    {
        byte[] Encrypt(byte[] message);
        byte[] Decrypt(byte[] cypher);
    }
}
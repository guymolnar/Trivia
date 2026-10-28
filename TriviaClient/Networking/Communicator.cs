using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using TriviaClient.Models;

namespace TriviaClient.Networking
{
    public class Communicator
    {
        private const string Server = "127.0.0.1";
        private const int PORT = 8826;
        private static byte[] AES_KEY = new byte[] {
            0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
            0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f
        };
        private ICryptoAlgorithm _crypto = new AesCryptoAlgorithm(AES_KEY);
        private TcpClient? _client;
        private NetworkStream? _stream;

        private static Communicator? _instance;
        public static Communicator Instance => _instance ??= new Communicator();
        private Communicator() { }

        public void Connect()
        {
            _client = new TcpClient(Server, PORT);
            _stream = this._client.GetStream();
        }
        public void Disconnect()
        {
            _stream?.Close();
            _client?.Close();
        }
        public void SendRequest(byte code, IRequest request)
        {
            byte[] serialized = JsonSerializer.Serialize(code, request); 
            byte[] body = serialized.Skip(5).ToArray(); 
            byte[] cipher = _crypto.Encrypt(body);

            byte[] length = BitConverter.GetBytes(cipher.Length);
            if (BitConverter.IsLittleEndian) 
            { 
                Array.Reverse(length); 
            }

            byte[] packet = new byte[1 + 4 + cipher.Length];
            packet[0] = code;
            Array.Copy(length, 0, packet, 1, 4);
            Array.Copy(cipher, 0, packet, 5, cipher.Length);
            _stream?.Write(packet, 0, packet.Length);
        }
        public (byte code, string json) ReceiveResponse()
        {
            byte[] header = new byte[5];
            int bytesRead = 0;
            while (bytesRead < 5)
            {
                bytesRead += _stream!.Read(header, bytesRead, 5 - bytesRead);
            }
            byte code = header[0];
            byte[] lenBytes = new byte[] { header[1], header[2], header[3], header[4] };
            if (BitConverter.IsLittleEndian)
            {
                Array.Reverse(lenBytes);
            }

            int length = BitConverter.ToInt32(lenBytes, 0);

            byte[] body = new byte[length];
            bytesRead = 0;
            while (bytesRead < length)
            {
                bytesRead += _stream!.Read(body, bytesRead, length - bytesRead);
            }
            byte[] plain = _crypto.Decrypt(body);
            return (code, Encoding.UTF8.GetString(plain));
        }
    }
}

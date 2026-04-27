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
        
        private TcpClient? _client;
        private NetworkStream? _stream;

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
            byte[] buffer = JsonSerializer.Serialize(code, request);
            _stream?.Write(buffer, 0, buffer.Length);
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
            return (code, Encoding.UTF8.GetString(body));
        }
    }
}

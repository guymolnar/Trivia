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
        public void SendRequest(byte code, IRequest request);
        public (byte code, string json) ReceiveResponse();
    }
}

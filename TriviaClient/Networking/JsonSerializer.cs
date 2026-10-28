using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using TriviaClient.Models;

namespace TriviaClient.Networking
{
    public static class JsonSerializer
    {
        public static byte[] Serialize(byte code, IRequest request)
        {
            string json = JsonConvert.SerializeObject(request); //Wow this is so easy in c#
            byte[] body = Encoding.UTF8.GetBytes(json);

            byte[] length = BitConverter.GetBytes(body.Length);
            if(BitConverter.IsLittleEndian)
            {
                Array.Reverse(length);
            }

            byte[] packet = new byte[1 + 4 + body.Length];
            packet[0] = code;
            Array.Copy(length, 0 , packet, 1, 4);
            Array.Copy(body, 0, packet, 5, body.Length);
            return packet;
        }
    }
}

using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Networking
{
    public static class JsonDeserializer
    {
        public static T Deserialize<T>(string json)
        {
            return JsonConvert.DeserializeObject<T>(json)!; //Genuinly amazed by how simple this is in c#
            //Theres a ! at the end because vs gave me an annoying warning that it can return NULL so i searched online how to fix it.
        }
    }
}

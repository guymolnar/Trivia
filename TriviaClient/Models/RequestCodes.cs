using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Models
{
    public static class RequestCodes
    {
        public const byte LOGIN_REQUEST_CODE = 201;
        public const byte SIGNUP_REQUEST_CODE = 202;
        public const byte GET_PLAYERS_REQUEST_CODE = 203;
        public const byte JOIN_ROOM_REQUEST_CODE = 204;
        public const byte CREATE_ROOM_REQUEST_CODE = 205;
        public const byte HIGH_SCORE_REQUEST_CODE = 206;
        public const byte LOGOUT_REQUEST_CODE = 207;
        public const byte GET_ROOMS_REQUEST_CODE = 208;
        public const byte PERSONAL_STATS_REQUEST_CODE = 209;
    }
}

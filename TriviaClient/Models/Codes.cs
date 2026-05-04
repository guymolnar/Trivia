using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Models
{
    public static class Codes
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
        public const byte CLOSE_ROOM_REQUEST_CODE = 210;
        public const byte START_GAME_REQUEST_CODE = 211;
        public const byte GET_ROOM_STATE_REQUEST_CODE = 212;
        public const byte LEAVE_ROOM_REQUEST_CODE = 213;

        public const byte ERROR_RESPONSE_CODE = 100;
        public const byte CLOSE_ROOM_RESPONSE_CODE = 110;
        public const byte START_GAME_RESPONSE_CODE = 111;
        public const byte LEAVE_ROOM_RESPONSE_CODE = 113;
    }
}

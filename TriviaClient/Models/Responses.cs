using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Models
{
    public class ErrorResponse
    {
        public string? message;
    }

    public class LoginResponse
    {
        public int status;
    }

    public class SignupResponse
    {
        public int status;
    }

    public class LogoutResponse
    {
        public int status;
    }

    public class GetRoomsResponse
    {
        public int status;
        public string? Rooms;
    }

    public class GetHighScoreResponse
    {
        public int status;
        public string? HighScores;
    }

    public class GetPersonalStatsResponse
    {
        public int status;
        public string? UserStatistics;
    }

    public class GetPlayersInRoomResponse
    {
        public string? PlayersInRoom;
    }

    public class JoinRoomResponse
    {
        public int status;
    }

    public class CreateRoomResponse
    {
        public int status;
    }

}
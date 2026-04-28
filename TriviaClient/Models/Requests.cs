using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Models
{
    public abstract class IRequest 
    {

    }

    //Q: Why are there ?'s?
    //A: because without it the vs warns that strings are non-nullable
    //And it's kind of annoying

    public class LogoutRequest : IRequest { }

    public class HighScoreRequest : IRequest { }

    public class PersonalStatsRequest : IRequest { }

    public class GetRoomsRequest : IRequest { }
    public class LoginRequest : IRequest
    {
        public string? username;
        public string? password;
    }

    public class SignupRequest : IRequest
    {
        public string? username;
        public string? password;
        public string? mail;
        public string? address;
        public string? phone;
        public string? birthday;
    }

    public class GetPlayersInRoomRequest : IRequest
    {
        public int roomId;
    }

    public class JoinRoomRequest : IRequest
    {
        public int roomId;
    }
    
    public class CreateRoomRequest : IRequest
    {
        public string? roomName;
        public int maxUsers;
        public int questionsCount;
        public int answersTimeout;
    }
}
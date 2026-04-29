using System.Windows;
using TriviaClient.Models;
using TriviaClient.Networking;
using static TriviaClient.Models.RequestCodes;

namespace TriviaClient
{
    public partial class RoomLobbyWindow : Window
    {
        private string _username;

        public RoomLobbyWindow(string username, string roomName, int roomId)
        {
            InitializeComponent();
            _username = username;
            txtRoomName.Text = roomName;
            try
            {
                Communicator.Instance.SendRequest(GET_PLAYERS_REQUEST_CODE, new GetPlayersInRoomRequest
                {
                    roomId = roomId,
                });
                var (code, json) = Communicator.Instance.ReceiveResponse();

                if (code == 100)
                {
                    lstPlayers.Items.Add("Failed to load players.");
                    return;
                }

                var response = JsonDeserializer.Deserialize<GetPlayersInRoomResponse>(json);
                if (string.IsNullOrEmpty(response.PlayersInRoom))
                {
                    lstPlayers.Items.Add("No players yet.");
                    return;
                }

                var players = response.PlayersInRoom.Split(", ");
                foreach (var player in players)
                {
                    lstPlayers.Items.Add(player);
                }
                txtAdmin.Text = $"Admin: {players[0]}";
            }
            catch (Exception ex)
            {
                lstPlayers.Items.Add(ex.Message);
            }
        }

        private void btnLeave_Click(object sender, RoutedEventArgs e)
        {
            HubWindow hub = new HubWindow(_username);
            hub.Show();
            this.Close();
        }

        private void btnCloseRoom_Click(object sender, RoutedEventArgs e)
        {
        }

        private void btnStartGame_Click(object sender, RoutedEventArgs e)
        {
        }
    }
}

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
                Communicator.Instance.SendRequest(GET_ROOM_STATE_REQUEST_CODE, new GetRoomStateRequest
                {
                    roomId = roomId,
                });
                var (code, json) = Communicator.Instance.ReceiveResponse();

                if (code == 100)
                {
                    lstPlayers.Items.Add("Failed to load players.");
                    return;
                }

                var response = JsonDeserializer.Deserialize<GetRoomStateResponse>(json);
                if (response.players == null || response.players.Count == 0)
                {
                    lstPlayers.Items.Add("No players yet.");
                    return;
                }
                btnCloseRoom.Visibility = (response.players[0] == _username) ? Visibility.Visible : Visibility.Collapsed;
                btnStartGame.Visibility = (response.players[0] == _username) ? Visibility.Visible : Visibility.Collapsed;
                btnLeave.Visibility = (response.players[0] == _username) ? Visibility.Collapsed : Visibility.Visible;
                foreach (var player in response.players)
                {
                    lstPlayers.Items.Add(player);
                }
                txtAdmin.Text = $"Admin: {response.players[0]}";
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

using System.Windows;
using TriviaClient.Models;
using TriviaClient.Networking;
using static TriviaClient.Models.RequestCodes;

namespace TriviaClient
{
    public partial class JoinRoomWindow : Window
    {
        private string _username;
        private List<string> _roomNames = new List<string>();
        public JoinRoomWindow(string username)
        {
            InitializeComponent();
            _username = username;
            try
            {
                Communicator.Instance.SendRequest(GET_ROOMS_REQUEST_CODE, new GetRoomsRequest { });
                var (code, json) = Communicator.Instance.ReceiveResponse();
                if (code == 100)
                {
                    txtError.Text = "Failed to load rooms.";
                    return;
                }
                var response = JsonDeserializer.Deserialize<GetRoomsResponse>(json);
                if (string.IsNullOrEmpty(response.Rooms))
                {
                    txtError.Text = "No rooms available.";
                    return;
                }
                _roomNames = response.Rooms.Split(", ").ToList();
                foreach (var roomName in _roomNames)
                {
                    lstRooms.Items.Add(roomName);
                }
            }
            catch (Exception ex)
            {
                txtError.Text = ex.Message;
            }
        }

        private void btnJoin_Click(object sender, RoutedEventArgs e)
        {
            if (lstRooms.SelectedItem == null)
            {
                txtError.Text = "Please select a room.";
                return;
            }
            int roomId = lstRooms.SelectedIndex;
            try
            {
                Communicator.Instance.SendRequest(JOIN_ROOM_REQUEST_CODE, new JoinRoomRequest
                {
                    roomId = roomId
                });
                var (code, json) = Communicator.Instance.ReceiveResponse();
                if (code == 100)
                {
                    txtError.Text = "Failed to join rooms.";
                    return;
                }
                var response = JsonDeserializer.Deserialize<JoinRoomResponse>(json);
                if (response.status == 0)
                {
                    txtError.Text = "Could not join room.";
                    return;
                }
                RoomLobbyWindow lobby = new RoomLobbyWindow(_username, _roomNames[roomId], roomId);
                lobby.Show();
            }
            catch (Exception ex)
            {
                txtError.Text = ex.Message;
            }
        }

        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            HubWindow hub = new HubWindow(_username);
            hub.Show();
            this.Close();
        }
    }
}
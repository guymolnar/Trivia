using System.Windows;
using TriviaClient.Models;
using TriviaClient.Networking;
using static TriviaClient.Models.Codes;

namespace TriviaClient
{
    public partial class JoinRoomWindow : Window
    {
        private string _username;
        private List<string> _roomNames = new List<string>();
        private List<int> _roomIds = new List<int>();

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
                foreach (var entry in response.Rooms.Split(", "))
                {
                    int colonIdx = entry.IndexOf(':');
                    if (colonIdx < 0) continue;
                    int id = int.Parse(entry.Substring(0, colonIdx));
                    string name = entry.Substring(colonIdx + 1);
                    _roomIds.Add(id);
                    _roomNames.Add(name);
                    lstRooms.Items.Add(name);
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
            int selectedIndex = lstRooms.SelectedIndex;
            int roomId = _roomIds[selectedIndex];
            try
            {
                Communicator.Instance.SendRequest(JOIN_ROOM_REQUEST_CODE, new JoinRoomRequest
                {
                    roomId = roomId
                });
                var (code, json) = Communicator.Instance.ReceiveResponse();
                if (code == 100)
                {
                    txtError.Text = "Failed to join room.";
                    return;
                }
                var response = JsonDeserializer.Deserialize<JoinRoomResponse>(json);
                if (response.status == 0)
                {
                    txtError.Text = "Could not join room.";
                    return;
                }
                RoomLobbyWindow lobby = new RoomLobbyWindow(_username, _roomNames[selectedIndex], roomId);
                lobby.Show();
                this.Close();
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
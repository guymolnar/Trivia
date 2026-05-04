using System.Threading;
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
        private Thread? _refreshingThread;
        private volatile bool _refreshing = false;

        public JoinRoomWindow(string username)
        {
            InitializeComponent();
            _username = username;
            LoadRooms();
            StartRefreshing();
        }

        private void LoadRooms()
        {
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

                List<int> newIds = new List<int>();
                List<string> newNames = new List<string>();

                if (!string.IsNullOrEmpty(response.Rooms))
                {
                    foreach (var entry in response.Rooms.Split(", "))
                    {
                        int colonIdx = entry.IndexOf(':');
                        if (colonIdx < 0) continue;
                        int id = int.Parse(entry.Substring(0, colonIdx));
                        string name = entry.Substring(colonIdx + 1);
                        newIds.Add(id);
                        newNames.Add(name);
                    }
                }

                _roomIds = newIds;
                _roomNames = newNames;

                Dispatcher.Invoke(() =>
                {
                    int selectedIndex = lstRooms.SelectedIndex;
                    lstRooms.Items.Clear();
                    foreach (var name in newNames)
                        lstRooms.Items.Add(name);
                    if (selectedIndex >= 0 && selectedIndex < lstRooms.Items.Count)
                    { 
                        lstRooms.SelectedIndex = selectedIndex; 
                    }
                    txtError.Text = newNames.Count == 0 ? "No rooms available." : "";
                });
            }
            catch (Exception ex)
            {
                Dispatcher.Invoke(() => txtError.Text = ex.Message);
            }
        }

        private void StartRefreshing()
        {
            _refreshing = true;
            _refreshingThread = new Thread(() =>
            {
                while (_refreshing)
                {
                    Thread.Sleep(1000);
                    if (!_refreshing) break;
                    LoadRooms();
                }
            });
            _refreshingThread.IsBackground = true;
            _refreshingThread.Start();
        }

        private void StopRefreshing()
        {
            _refreshing = false;
            _refreshingThread?.Join();
        }

        private void btnJoin_Click(object sender, RoutedEventArgs e)
        {
            if (lstRooms.SelectedItem == null)
            {
                txtError.Text = "Please select a room.";
                return;
            }
            StopRefreshing();
            int selectedIndex = lstRooms.SelectedIndex;
            int roomId = _roomIds[selectedIndex];
            try
            {
                Communicator.Instance.SendRequest(JOIN_ROOM_REQUEST_CODE, new JoinRoomRequest { roomId = roomId });
                var (code, json) = Communicator.Instance.ReceiveResponse();
                if (code == 100)
                {
                    txtError.Text = "Failed to join room.";
                    StartRefreshing();
                    return;
                }
                var response = JsonDeserializer.Deserialize<JoinRoomResponse>(json);
                if (response.status == 0)
                {
                    txtError.Text = "Could not join room.";
                    StartRefreshing();
                    return;
                }
                RoomLobbyWindow lobby = new RoomLobbyWindow(_username, _roomNames[selectedIndex], roomId);
                lobby.Show();
                this.Close();
            }
            catch (Exception ex)
            {
                txtError.Text = ex.Message;
                StartRefreshing();
            }
        }

        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            StopRefreshing();
            HubWindow hub = new HubWindow(_username);
            hub.Show();
            this.Close();
        }
    }
}
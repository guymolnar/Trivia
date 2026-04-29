using System.Threading;
using System.Windows;
using TriviaClient.Models;
using TriviaClient.Networking;
using static TriviaClient.Models.Codes;

namespace TriviaClient
{
    public partial class RoomLobbyWindow : Window
    {
        private string _username;
        private bool _isAdmin;
        private int _roomId;
        private Thread? _listenerThread;
        private volatile bool _listening = false;

        public RoomLobbyWindow(string username, string roomName, int roomId)
        {
            InitializeComponent();
            _username = username;
            _roomId = roomId;
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

                foreach (var player in response.players)
                    lstPlayers.Items.Add(player);

                if (response.players.Count > 0)
                {
                    txtAdmin.Text = $"Admin: {response.players[0]}";
                    bool isAdmin = response.players[0] == _username;
                    _isAdmin = isAdmin;
                    btnCloseRoom.Visibility = isAdmin ? Visibility.Visible : Visibility.Collapsed;
                    btnStartGame.Visibility = isAdmin ? Visibility.Visible : Visibility.Collapsed;
                    btnLeave.Visibility = isAdmin ? Visibility.Collapsed : Visibility.Visible;
                }
            }
            catch (Exception ex)
            {
                lstPlayers.Items.Add(ex.Message);
            }
            if (!_isAdmin)
            {
                StartListening();
            }
        }

        private void StartListening()
        {
            _listening = true;
            _listenerThread = new Thread(() =>
            {
                try
                {
                    while (_listening)
                    {
                        var (code, json) = Communicator.Instance.ReceiveResponse();

                        if (code == LEAVE_ROOM_RESPONSE_CODE)
                        {
                            Dispatcher.Invoke(() =>
                            {
                                MessageBox.Show("The room was closed by the admin.", "Room Closed");
                                HubWindow hub = new HubWindow(_username);
                                hub.Show();
                                this.Close();
                            });
                            break;
                        }
                        else if (code == START_GAME_RESPONSE_CODE)
                        {
                            Dispatcher.Invoke(() =>
                            {
                                
                            });
                            break;
                        }
                    }
                }
                catch { }
            });
            _listenerThread.IsBackground = true;
            _listenerThread.Start();
        }

        private void StopListening()
        {
            _listening = false;
        }

        private void btnLeave_Click(object sender, RoutedEventArgs e)
        {
            StopListening();
            try
            {
                Communicator.Instance.SendRequest(LEAVE_ROOM_REQUEST_CODE, new LeaveRoomRequest { roomId = _roomId });
                var (code, json) = Communicator.Instance.ReceiveResponse();
                var response = JsonDeserializer.Deserialize<LeaveRoomResponse>(json);

                if (code == 100 || response.status == 0)
                {
                    MessageBox.Show("Could not leave room.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    StartListening();
                    return;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                StartListening();
                return;
            }

            HubWindow hub = new HubWindow(_username);
            hub.Show();
            this.Close();
        }

        private void btnCloseRoom_Click(object sender, RoutedEventArgs e)
        {
            StopListening();
            try
            {
                Communicator.Instance.SendRequest(CLOSE_ROOM_REQUEST_CODE, new CloseRoomRequest { roomId = _roomId });
                var (code, json) = Communicator.Instance.ReceiveResponse();
                var response = JsonDeserializer.Deserialize<CloseRoomResponse>(json);

                if (code == 100 || response.status == 0)
                {
                    MessageBox.Show("Could not close room.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    StartListening();
                    return;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                StartListening();
                return;
            }

            HubWindow hub = new HubWindow(_username);
            hub.Show();
            this.Close();
        }

        private void btnStartGame_Click(object sender, RoutedEventArgs e)
        {
            StopListening();
            try
            {
                Communicator.Instance.SendRequest(START_GAME_REQUEST_CODE, new StartGameRequest { roomId = _roomId });
                var (code, json) = Communicator.Instance.ReceiveResponse();
                var response = JsonDeserializer.Deserialize<StartGameResponse>(json);

                if (code == 100 || response.status == 0)
                {
                    MessageBox.Show("Could not start game.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    StartListening();
                    return;
                }

                // TODO: open game window
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                StartListening();
            }
        }
    }
}
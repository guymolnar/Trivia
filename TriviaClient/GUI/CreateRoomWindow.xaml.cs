using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using TriviaClient.Models;
using TriviaClient.Networking;
using static TriviaClient.Models.RequestCodes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        private string _username;

        public CreateRoomWindow(string username)
        {
            InitializeComponent();
            _username = username;
        }

        private void backToMenuBtn_click(object sender, RoutedEventArgs e)
        {
            HubWindow hub = new HubWindow(_username);
            hub.Show();
            this.Close();
        }

        private void createRoomBtn_click(object sender, RoutedEventArgs e)
        {
            try
            {
                Communicator.Instance.Connect();
                Communicator.Instance.SendRequest(CREATE_ROOM_REQUEST_CODE, new CreateRoomRequest
                {
                    roomName = roomName.Text,
                    questionsCount = int.Parse(numOfQuestions.Text),
                    answersTimeout = int.Parse(timePerQuestion.Text),
                    maxUsers = int.Parse(numOfPlayers.Text),
                });

                var (code, json) = Communicator.Instance.ReceiveResponse();
                var response = JsonDeserializer.Deserialize<CreateRoomResponse>(json);

                if (response.status == 0 || code == 100)
                {
                    txtError.Text = "Invalid Room Creation";
                    return;
                }
                RoomLobbyWindow lobby = new RoomLobbyWindow(_username, roomName.Text, _username);
                lobby.Show();
                this.Close();
            }
            catch (Exception ex)
            {
                txtError.Text = "Could not connect to server.";
            }
        }
    }
}

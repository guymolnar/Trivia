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
            // TODO: send create room request to server
            RoomLobbyWindow lobby = new RoomLobbyWindow(_username, roomName.Text, _username);
            lobby.Show();
            this.Close();
        }
    }
}

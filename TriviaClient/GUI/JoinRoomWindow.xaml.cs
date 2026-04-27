using System.Windows;

namespace TriviaClient
{
    public partial class JoinRoomWindow : Window
    {
        private string _username;

        public JoinRoomWindow(string username)
        {
            InitializeComponent();
            _username = username;
            // TODO: load rooms from server
        }

        private void btnJoin_Click(object sender, RoutedEventArgs e)
        {
            if (lstRooms.SelectedItem == null)
            {
                txtError.Text = "Please select a room.";
                return;
            }
            RoomLobbyWindow lobby = new RoomLobbyWindow(_username, lstRooms.SelectedItem.ToString(), "Admin");
            lobby.Show();
            this.Close();
        }

        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            HubWindow hub = new HubWindow(_username);
            hub.Show();
            this.Close();
        }
    }
}
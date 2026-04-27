using System.Windows;

namespace TriviaClient
{
    public partial class RoomLobbyWindow : Window
    {
        private string _username;

        public RoomLobbyWindow(string username, string roomName, string admin)
        {
            InitializeComponent();
            _username = username;
            txtRoomName.Text = roomName;
            txtAdmin.Text = $"Admin: {admin}";
            // TODO: load players from server
        }

        private void btnLeave_Click(object sender, RoutedEventArgs e)
        {
            HubWindow hub = new HubWindow(_username);
            hub.Show();
            this.Close();
        }
    }
}
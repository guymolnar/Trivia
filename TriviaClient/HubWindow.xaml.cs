using System.Windows;

namespace TriviaClient
{
    public partial class HubWindow : Window
    {
        private string _username;

        public HubWindow(string username)
        {
            InitializeComponent();
            _username = username;
            txtWelcome.Text = $"Welcome, {username}!";
        }

        private void btnJoinRoom_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomWindow joinRoom = new JoinRoomWindow(_username);
            joinRoom.Show();
            this.Close();
        }

        private void btnCreateRoom_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomWindow createRoomWindow = new CreateRoomWindow(_username);
            createRoomWindow.Show();
            this.Close();
        }

        private void btnMyStats_Click(object sender, RoutedEventArgs e)
        {
            StatisticsWindow stats = new StatisticsWindow(_username);
            stats.Show();
            this.Close();
        }

        private void btnBestScores_Click(object sender, RoutedEventArgs e)
        {
            HighScoresWindow highScores = new HighScoresWindow(_username);
            highScores.Show();
            this.Close();
        }

        private void btnLogout_Click(object sender, RoutedEventArgs e)
        {
            LoginWindow login = new LoginWindow();
            login.Show();
            this.Close();
        }
    }
}

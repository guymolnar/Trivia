using System.Windows;

namespace TriviaClient
{
    public partial class HubWindow : Window
    {
        public HubWindow(string username)
        {
            InitializeComponent();
            txtWelcome.Text = $"Welcome, {username}!";
        }

        private void btnJoinRoom_Click(object sender, RoutedEventArgs e)
        {
            // join room logic will go here
        }

        private void btnCreateRoom_Click(object sender, RoutedEventArgs e)
        {
            // create room logic will go here
        }

        private void btnMyStats_Click(object sender, RoutedEventArgs e)
        {
            // personal stats logic will go here
        }

        private void btnBestScores_Click(object sender, RoutedEventArgs e)
        {
            // best scores logic will go here
        }

        private void btnLogout_Click(object sender, RoutedEventArgs e)
        {
            LoginWindow login = new LoginWindow();
            login.Show();
            this.Close();
        }
    }
}

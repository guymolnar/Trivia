using System.Windows;

namespace TriviaClient
{
    public partial class StatisticsWindow : Window
    {
        private string _username;

        public StatisticsWindow(string username)
        {
            InitializeComponent();
            _username = username;
        }

        private void btnPersonalStats_Click(object sender, RoutedEventArgs e)
        {
            PersonalStatsWindow personalStats = new PersonalStatsWindow(_username);
            personalStats.Show();
            this.Close();
        }

        private void btnHighScores_Click(object sender, RoutedEventArgs e)
        {
            HighScoresWindow highScores = new HighScoresWindow(_username);
            highScores.Show();
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

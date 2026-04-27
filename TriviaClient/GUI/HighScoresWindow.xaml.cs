using System.Windows;

namespace TriviaClient
{
    public partial class HighScoresWindow : Window
    {
        private string _username;

        public HighScoresWindow(string username)
        {
            InitializeComponent();
            _username = username;
        }

        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            StatisticsWindow stats = new StatisticsWindow(_username);
            stats.Show();
            this.Close();
        }
    }
}

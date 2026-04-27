using System.Windows;

namespace TriviaClient
{
    public partial class PersonalStatsWindow : Window
    {
        private string _username;

        public PersonalStatsWindow(string username)
        {
            InitializeComponent();
            _username = username;
            // TODO: load personal stats from server
        }

        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            StatisticsWindow stats = new StatisticsWindow(_username);
            stats.Show();
            this.Close();
        }
    }
}

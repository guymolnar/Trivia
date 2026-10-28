using System.Windows;
using TriviaClient.Models;
using TriviaClient.Networking;
using static TriviaClient.Models.Codes;

namespace TriviaClient
{
    public partial class PersonalStatsWindow : Window
    {
        private string _username;

        public PersonalStatsWindow(string username)
        {
            InitializeComponent();
            _username = username;
            try
            {
                Communicator.Instance.SendRequest(PERSONAL_STATS_REQUEST_CODE, new PersonalStatsRequest());
                var (code, json) = Communicator.Instance.ReceiveResponse();

                if (code == 100)
                {
                    lstStats.Items.Add("Failed to load stats.");
                    return;
                }

                var response = JsonDeserializer.Deserialize<GetPersonalStatsResponse>(json);
                if (response.UserStatistics == null)
                {
                    lstStats.Items.Add("No stats yet.");
                    return;
                }
                foreach (var stat in response.UserStatistics)
                {
                    lstStats.Items.Add(stat);
                }
            }
            catch (Exception ex)
            {
                lstStats.Items.Add(ex.Message);
            }
        }

        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            StatisticsWindow stats = new StatisticsWindow(_username);
            stats.Show();
            this.Close();
        }
    }
}

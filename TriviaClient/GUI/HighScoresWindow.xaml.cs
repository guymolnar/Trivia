using System.Windows;
using TriviaClient.Models;
using TriviaClient.Networking;
using static TriviaClient.Models.RequestCodes;

namespace TriviaClient
{
    public partial class HighScoresWindow : Window
    {
        private string _username;

        public HighScoresWindow(string username)
        {
            InitializeComponent();
            _username = username;
            try
            {
                Communicator.Instance.SendRequest(HIGH_SCORE_REQUEST_CODE, new HighScoreRequest());
                var (code, json) = Communicator.Instance.ReceiveResponse();

                if (code == 100)
                {
                    lstHighScores.Items.Add("Failed to load scores.");
                    return;
                }

                var response = JsonDeserializer.Deserialize<GetHighScoreResponse>(json);
                int rank = 1;
                if (response.HighScores == null)
                {
                    lstHighScores.Items.Add("No scores yet.");
                    return;
                }
                foreach (var score in response.HighScores!)
                {
                    lstHighScores.Items.Add($"{rank++}. {score}");
                }
            }
            catch (Exception ex)
            {
                lstHighScores.Items.Add(ex.Message);
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

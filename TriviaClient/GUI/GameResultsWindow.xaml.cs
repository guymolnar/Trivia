using System.Collections.Generic;
using System.Linq;
using System.Windows;
using TriviaClient.Models;

namespace TriviaClient
{
    public partial class GameResultsWindow : Window
    {
        private string _username;

        public GameResultsWindow(string username, List<PlayerResults> results)
        {
            InitializeComponent();
            _username = username;

            var sorted = results.OrderByDescending(r => r.correctAnswerCount).ThenBy(r => r.averageAnswerTime).ToList();

            string winner = sorted.Count > 0 ? sorted[0].username ?? "?" : "?";
            txtWinner.Text = winner == _username ? "You won!" : $"Winner: {winner}";

            for (int i = 0; i < sorted.Count; i++)
            {
                var r = sorted[i];
                lstResults.Items.Add($"{i + 1}. {r.username}  |  Correct: {r.correctAnswerCount}  |  Wrong: {r.wrongAnswerCount}  |  Avg Time: {r.averageAnswerTime}s");
            }
        }

        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            HubWindow hub = new HubWindow(_username);
            hub.Show();
            this.Close();
        }
    }
}
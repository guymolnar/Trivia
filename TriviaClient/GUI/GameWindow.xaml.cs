using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Threading;
using TriviaClient.Models;
using TriviaClient.Networking;
using static TriviaClient.Models.Codes;

namespace TriviaClient
{
    public partial class GameWindow : Window
    {
        private string _username;
        private int _totalQuestions;
        private int _answerTimeout;
        private int _answeredCount = 0;
        private int _correctCount = 0;
        private int _timeLeft;
        private DateTime _questionStartTime;
        private DispatcherTimer _timer;
        private bool _answered = false;
        private bool _closedByButton = false;
        private Dictionary<int, Button> _answerButtons;

        public GameWindow(string username, int totalQuestions, int answerTimeout)
        {
            InitializeComponent();
            _username = username;
            _totalQuestions = totalQuestions;
            _answerTimeout = answerTimeout;

            _answerButtons = new Dictionary<int, Button>
            {
                { 1, btn1 }, { 2, btn2 }, { 3, btn3 }, { 4, btn4 }
            };

            _timer = new DispatcherTimer();
            _timer.Interval = TimeSpan.FromSeconds(1);
            _timer.Tick += Timer_Tick;

            LoadNextQuestion();
        }

        private void LoadNextQuestion()
        {
            _answered = false;
            ResetButtonColors();
            SetButtonsEnabled(true);

            try
            {
                Communicator.Instance.SendRequest(GET_QUESTION_REQUEST_CODE, new GetQuestionRequest());
                var (code, json) = Communicator.Instance.ReceiveResponse();
                var response = JsonDeserializer.Deserialize<GetQuestionResponse>(json);

                if (code == ERROR_RESPONSE_CODE || response.status == 0 || response.answers == null)
                {
                    PollForResults();
                    return;
                }

                txtQuestion.Text = response.question;
                txtQuestionNum.Text = $"Q {_answeredCount + 1}/{_totalQuestions}";
                txtCorrect.Text = $"{_correctCount} correct";

                foreach (var kvp in response.answers)
                {
                    if (_answerButtons.ContainsKey(kvp.Key))
                    {
                        _answerButtons[kvp.Key].Content = kvp.Value;

                    }
                }

                _timeLeft = _answerTimeout;
                txtTimer.Text = $"{_timeLeft}s";
                _questionStartTime = DateTime.Now;
                _timer.Start();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }
        }

        private void Timer_Tick(object? sender, EventArgs e)
        {
            _timeLeft--;
            txtTimer.Text = $"{_timeLeft}s";

            if (_timeLeft <= 0)
            {
                _timer.Stop();
                if (!_answered)
                {
                    SubmitAnswer(0);

                }
            }
        }

        private void Answer_Click(object sender, RoutedEventArgs e)
        {
            if (_answered) return;
            _timer.Stop();
            int answerId = int.Parse(((Button)sender).Tag.ToString()!);
            SubmitAnswer(answerId);
        }

        private void SubmitAnswer(int answerId)
        {
            _answered = true;
            SetButtonsEnabled(false);
            int elapsed = (int)(DateTime.Now - _questionStartTime).TotalSeconds;

            try
            {
                Communicator.Instance.SendRequest(SUBMIT_ANSWER_REQUEST_CODE, new SubmitAnswerRequest
                {
                    answerId = answerId,
                    answerTime = elapsed
                });
                var (code, json) = Communicator.Instance.ReceiveResponse();
                var response = JsonDeserializer.Deserialize<SubmitAnswerResponse>(json);

                int correctId = response.correctAnswerId;

                if (_answerButtons.ContainsKey(correctId))
                { 
                    _answerButtons[correctId].Background = Brushes.LightGreen; 
                }

                if (answerId != 0 && answerId != correctId && _answerButtons.ContainsKey(answerId))
                {
                    _answerButtons[answerId].Background = Brushes.LightCoral;
                }

                if (answerId == correctId)
                {
                    _correctCount++;
                }
                _answeredCount++;
                txtCorrect.Text = $"{_correctCount} correct";
                txtQuestionNum.Text = $"Q {_answeredCount}/{_totalQuestions}";
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }

            var delay = new DispatcherTimer { Interval = TimeSpan.FromSeconds(2) };
            delay.Tick += (s, e2) => { delay.Stop(); LoadNextQuestion(); };
            delay.Start();
        }

        private void PollForResults()
        {
            SetButtonsEnabled(false);
            txtQuestion.Text = "Game finished!";
            txtTimer.Text = "";
            foreach (var btn in _answerButtons.Values)
            {
                btn.Content = "";
            }
            try
            {
                Communicator.Instance.SendRequest(GET_GAME_RESULTS_REQUEST_CODE, new GetGameResultsRequest());
                var (code, json) = Communicator.Instance.ReceiveResponse();
                var response = JsonDeserializer.Deserialize<GetGameResultsResponse>(json);

                GameResultsWindow results = new GameResultsWindow(_username, response.results!);
                results.Show();
                _closedByButton = true;
                this.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }
        }

        private void ResetButtonColors()
        {
            foreach (var btn in _answerButtons.Values)
            {
                btn.ClearValue(BackgroundProperty);
            }
        }

        private void SetButtonsEnabled(bool enabled)
        {
            foreach (var btn in _answerButtons.Values)
            {
                btn.IsEnabled = enabled;
            }
        }

        private void btnLeave_Click(object sender, RoutedEventArgs e)
        {
            _timer.Stop();
            try
            {
                Communicator.Instance.SendRequest(LEAVE_GAME_REQUEST_CODE, new LeaveGameRequest());
                Communicator.Instance.ReceiveResponse();
            }
            catch { }
            HubWindow hub = new HubWindow(_username);
            hub.Show();
            _closedByButton = true;
            this.Close();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            _timer.Stop();
            if (_closedByButton) return;
            try
            {
                Communicator.Instance.SendRequest(LEAVE_GAME_REQUEST_CODE, new LeaveGameRequest());
                Communicator.Instance.ReceiveResponse();
            }
            catch { }
        }
    }
}
using System.Windows;
using TriviaClient.Models;
using TriviaClient.Networking;
using static TriviaClient.Models.RequestCodes;

namespace TriviaClient
{
    public partial class LoginWindow : Window
    {
        public LoginWindow()
        {
            InitializeComponent();
        }

        private void btnLogin_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Communicator.Instance.Connect();
                Communicator.Instance.SendRequest(LOGIN_REQUEST_CODE, new LoginRequest
                {
                    username = txtUsername.Text,
                    password = txtPassword.Password,
                });

                var (code, json) = Communicator.Instance.ReceiveResponse();
                var response = JsonDeserializer.Deserialize<LoginResponse>(json);

                if (response.status == 0)
                {
                    txtError.Text = "Invalid login.";
                    return;
                }
                HubWindow hub = new HubWindow(txtUsername.Text);
                hub.Show();
                this.Close();
            }   
            catch (Exception ex) 
            {
                txtError.Text = "Could not connect to server.";
            }
        }

        private void btnSignup_Click(object sender, RoutedEventArgs e)
        {
            SignupWindow signup = new SignupWindow();
            signup.Show();
            this.Close();
        }

        private void btnMainMenu_Click(object sender, RoutedEventArgs e)
        {
            MainWindow main = new MainWindow();
            main.Show();
            this.Close();
        }
    }
}

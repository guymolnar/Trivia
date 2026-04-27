using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using TriviaClient.Models;
using TriviaClient.Networking;
using static TriviaClient.Models.RequestCodes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {
        public SignupWindow()
        {
            InitializeComponent();
        }
        private void btnSignup_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Communicator.Instance.Connect();
                Communicator.Instance.SendRequest(SIGNUP_REQUEST_CODE, new SignupRequest
                {
                    username = txtUsername.Text,
                    password = txtPassword.Password,
                    address = txtAddress.Text,
                    phone = txtPhone.Text,
                    birthday = txtBirthday.Text,
                    mail = txtEmail.Text,
                });

                var (code, json) = Communicator.Instance.ReceiveResponse();
                var response = JsonDeserializer.Deserialize<SignupResponse>(json);

                if (response.status == 0)
                {
                    txtError.Text = "Invalid Signup! check fields again.";
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


        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            LoginWindow login = new LoginWindow();
            login.Show();
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

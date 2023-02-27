using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;

namespace WebChat
{
    public partial class Form1 : Form
    {
        #region Konstante
        const int STD_PORT = 1234;
        const string STD_IP = "127.0.0.1";
        const int STD_MSG_SIZE = 1024;
        const int STD_HEAD_LEN = 1;
        const string STD_CRYPTO_KEY = "mojKljuč";
        NetworkStream ns;

        private bool run = false;
        #endregion

        public static string Encrypt(string message)
        {
            //https://stackoverflow.com/questions/4100996/c-sharp-encoding-in-des-encryption-decryption
            //Pretvori sporočilo in geslo v byte
            byte[] messageBytes = Encoding.ASCII.GetBytes(message);
            byte[] passwordBytes = Encoding.ASCII.GetBytes(STD_CRYPTO_KEY);

            //Nastavi enkripcijske nastavitve 
            DESCryptoServiceProvider provider = new DESCryptoServiceProvider();
            ICryptoTransform transform = provider.CreateEncryptor(passwordBytes, passwordBytes);
            CryptoStreamMode mode = CryptoStreamMode.Write;

            //Nastavi tok za kriptiranje
            MemoryStream memStream = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(memStream, transform, mode);
            cryptoStream.Write(messageBytes, 0, messageBytes.Length);
            cryptoStream.FlushFinalBlock();

            //Prebere kriptirano sporočilo iz pomnilnika
            byte[] encryptedMessageBytes = new byte[memStream.Length];
            memStream.Position = 0;
            memStream.Read(encryptedMessageBytes, 0, encryptedMessageBytes.Length);

            //Pretvori sporočilo na 64 bitno osnovo
            string encryptedMessage = Convert.ToBase64String(encryptedMessageBytes);

            return encryptedMessage;
        }

        public static string Decrypt(string message)
        {
            //https://stackoverflow.com/questions/4100996/c-sharp-encoding-in-des-encryption-decryption
            //Pretvori v Byte
            byte[] encryptedMessageBytes = Convert.FromBase64String(message);
            byte[] passwordBytes = ASCIIEncoding.ASCII.GetBytes(STD_CRYPTO_KEY);

            // Nastavi enkripcijske nastavitve 
            DESCryptoServiceProvider provider = new DESCryptoServiceProvider();
            ICryptoTransform transform = provider.CreateDecryptor(passwordBytes, passwordBytes);
            CryptoStreamMode mode = CryptoStreamMode.Write;

            //Nastavi toke in dekripcijo
            MemoryStream memStream = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(memStream, transform, mode);
            cryptoStream.Write(encryptedMessageBytes, 0, encryptedMessageBytes.Length);
            cryptoStream.FlushFinalBlock();

            //Prebere dekriprirano sporocilo
            byte[] decryptedMessageBytes = new byte[memStream.Length];
            memStream.Position = 0;
            memStream.Read(decryptedMessageBytes, 0, decryptedMessageBytes.Length);

            //Pretvori sporocilo v niz
            string decrypted = ASCIIEncoding.ASCII.GetString(decryptedMessageBytes);

            return decrypted;
        }

        static string Receive(NetworkStream ns)
        {
            try
            {
                byte[] recv = new byte[STD_MSG_SIZE];
                int lenght = ns.Read(recv, 0, recv.Length);
                return Encoding.UTF8.GetString(recv, 0, lenght);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Napaka pri prejemniku!\n" + ex.Message + "\n" + ex.StackTrace);
                return null;
            }
        }

        static void Send(NetworkStream ns, string message)
        {
            try
            {
                byte[] send = Encoding.UTF8.GetBytes(message.ToCharArray(), 0, message.Length);
                ns.Write(send, 0, send.Length);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Napaka pri pošiljatelju!\n" + ex.Message + "\n" + ex.StackTrace);
            }
        }

        private void RecieveRequests(NetworkStream ns)
        {
            while (run)
            {
                string message = Receive(ns);
                messageDisplay.Invoke(new Action(() => messageDisplay.Text += message + "\n"));
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            messageBox.ReadOnly = true;
            messageDisplay.ReadOnly = true;
            quitBtn.Enabled = false;
            sendBtn.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //login button
            //messageDisplay.Text = "login button";

            try
            {
                TcpClient client = new TcpClient();
                client.Connect(STD_IP, STD_PORT);
                ns = client.GetStream();
                connectBtn.Enabled = false;
                sendBtn.Enabled = true;
                usernameBox.ReadOnly = true;
                messageBox.ReadOnly = false;
                quitBtn.Enabled = true;
                run = true;
                Send(ns, Encrypt("J|" + usernameBox.Text));

                Thread newThread = new Thread(new ThreadStart(() => RecieveRequests(ns)));
                newThread.IsBackground = true;
                try
                {
                    newThread.Start();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Napaka pri pošiljatelju!\n" + ex.Message + "\n" + ex.StackTrace);
                    newThread.Join();
                    client.Close();
                }

                

            }
            catch (Exception ex)
            {
                messageDisplay.Text += "Napaka pri povezovanju!\n" + ex.Message + "\n" + ex.StackTrace;
                run = false;

            }

        }

       

        private void button3_Click(object sender, EventArgs e)
        {
            //send button
            //messageDisplay.Text = "send button";

            Send(ns, Encrypt("M|" + messageBox.Text));
            messageBox.Text = "";
        }
        private void quitBtn_Click(object sender, EventArgs e)
        {
            //quit button
            //messageDisplay.Text = "quit button";

            connectBtn.Enabled = true;
            sendBtn.Enabled = false;
            quitBtn.Enabled = false;
            usernameBox.ReadOnly = false;
            messageBox.ReadOnly = true;
            run = false;
            Send(ns, Encrypt("L|cya"));
            //Application.ExitThread();
        }

        private void messageDisplay_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void messageDisplay_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
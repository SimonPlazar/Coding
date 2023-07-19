using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace HibridnoSifriranje
{
    public partial class Form1 : Form
    {

        #region Konstante
        const int STD_PORT = 1234;
        const string STD_IP = "127.0.0.1";
        const int STD_MSG_SIZE = 1024;
        const int STD_BLOCK_SIZE = 1024;
        const int STD_KEY_SIZE = 1024;
        bool isChecked;
        bool run = true;
        private Aes aes = null;
        private ECDiffieHellmanCng diffieHellman = null;
        string filePath;

        private Thread clientThread;
        private Thread serverThread;

        #endregion

        
        public static byte[] Encrypt(byte[] message, byte[] key, byte[] iv)
        {
            //Encoding.UTF8.GetString
            //Encoding.UTF8.GetBytes
            MD5CryptoServiceProvider mdc = new MD5CryptoServiceProvider();

            byte[] keyBytes = mdc.ComputeHash(key);
            mdc.Clear();

            TripleDESCryptoServiceProvider tdes = new TripleDESCryptoServiceProvider();
            tdes.Key = keyBytes;
            tdes.Mode = CipherMode.ECB;
            tdes.Padding = PaddingMode.PKCS7;

            var encryptor = tdes.CreateEncryptor();

            byte[] msgBytes = message;

            byte[] resultBytes = encryptor.TransformFinalBlock(msgBytes, 0, msgBytes.Length);

            tdes.Clear();

            return resultBytes;
        }

        public static byte[] Decrypt(byte[] message, byte[] key, byte[] iv)
        {
            //Encoding.UTF8.GetString
            //Encoding.UTF8.GetBytes
            MD5CryptoServiceProvider mdc = new MD5CryptoServiceProvider();

            byte[] keyBytes = mdc.ComputeHash(key);
            mdc.Clear();

            TripleDESCryptoServiceProvider tdes = new TripleDESCryptoServiceProvider();

            tdes.Key = keyBytes;
            tdes.Mode = CipherMode.ECB;
            tdes.Padding = PaddingMode.PKCS7;

            var encryptor = tdes.CreateDecryptor();

            byte[] resultBytes = encryptor.TransformFinalBlock(message, 0, message.Length);

            tdes.Clear();

            return resultBytes;
        }
        


        static byte[] Receive(NetworkStream ns)
        {
            try
            {
                byte[] recv = new byte[STD_MSG_SIZE];
                MemoryStream data = new MemoryStream();
                int lenght = ns.Read(recv, 0, recv.Length);

                while (lenght > 0)
                {
                    data.Write(recv, 0, lenght);
                    if (ns.DataAvailable)
                    {
                        lenght = ns.Read(recv, 0, recv.Length);
                    }
                    else break;
                }

                return data.ToArray();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Napaka pri prejemniku!\n" + ex.Message + "\n" + ex.StackTrace);
                return null;
            }
        }

        static void Send(NetworkStream ns, byte[] message)
        {
            try
            {
                byte[] send = message;
                ns.Write(send, 0, send.Length);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Napaka pri pošiljatelju!\n" + ex.Message + "\n" + ex.StackTrace);
            }
        }



        public Form1()
        {
            InitializeComponent();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            //dc

        }


        private void Sender()
        {
            try
            {   //Encoding.UTF8.GetString
                //Encoding.UTF8.GetBytes
                //Convert.FromBase64String
                //Convert.ToBase64String
                ECDiffieHellmanCng diffieHellman = new ECDiffieHellmanCng();
                diffieHellman.KeyDerivationFunction = ECDiffieHellmanKeyDerivationFunction.Hash;
                diffieHellman.HashAlgorithm = CngAlgorithm.Sha256;
                byte[] pubkey = diffieHellman.PublicKey.ToByteArray();

                TcpClient client = new TcpClient();
                client.Connect(STD_IP, STD_PORT);

                //richTextBox1.Text += "Tcp client ustvarjen\n";
                richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Tcp klient ustvarjen\n"));
                //IZMENJAVA KLJUCEV
                NetworkStream ns = client.GetStream();
                Send(ns, pubkey);
                //richTextBox1.Text += "Poslal javni kljuc: " + Convert.ToBase64String(pubkey) + "\n";
                richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Poslal javni kljuc: " + Convert.ToBase64String(pubkey) + "\n"));
                byte[] data = Receive(ns);
                //richTextBox1.Text += "Prejel javni kljuc: " + Convert.ToBase64String(data) + "\n";
                richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Prejel javni kljuc: " + Convert.ToBase64String(data) + "\n"));

                byte[] iv = Encoding.UTF8.GetBytes("setstanst1212");

                Send(ns, iv);

                richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Poslal iv: " + Encoding.UTF8.GetString(iv) + "\n"));

                byte[] key = diffieHellman.DeriveKeyMaterial(ECDiffieHellmanCngPublicKey.FromByteArray(data, CngKeyBlobFormat.EccPublicBlob));
                
                
                //PRENOS SIFRIRANIH PODATKOV

                string fileName = Path.GetFileName(filePath);
                FileStream fs = File.OpenRead(filePath);

                richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Prejel datoteko: " + fileName + "\n"));
                int repeats = Convert.ToInt32(Math.Ceiling( ((double)fs.Length/(double)STD_MSG_SIZE)));
                
                string msg = fileName + "|" + repeats.ToString();

                richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Sporocilo: " + msg + "\n"));

                byte[] encrypted = Encrypt(Encoding.UTF8.GetBytes(msg), key, iv);

                Send(ns, encrypted);
                
                byte[] buffer = null;
                int size = 0;
                
                
                while (repeats-- > 0) { 
                    buffer = new byte[STD_MSG_SIZE];
                    size = fs.Read(buffer, 0, STD_MSG_SIZE);

                    //size.ToString();
                    richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Prebral " + size.ToString() + "\n"));
                    //richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Buffer " + Encoding.UTF8.GetString(buffer) + "\n"));

                    if (size < STD_MSG_SIZE)
                        Array.Resize(ref buffer, size);
                    encrypted = Encrypt(buffer, key, iv);
                    Send(ns, encrypted);
                }

                fs.Close();

                richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Sporocilo poslano\n"));

                client.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Napaka!\n" + ex.Message + "\n" + ex.StackTrace);
            }

            clientThread.Join();
        }

        private void Receiver()
        {
            TcpListener server = new TcpListener(IPAddress.Parse(STD_IP), STD_PORT);
            server.Start();

            richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Tcp server ustvarjen\n"));
            //richTextBox1.Text += "Tcp server ustvarjen\n";

            ECDiffieHellmanCng diffieHellman = new ECDiffieHellmanCng();
            diffieHellman.KeyDerivationFunction = ECDiffieHellmanKeyDerivationFunction.Hash;
            diffieHellman.HashAlgorithm = CngAlgorithm.Sha256;
            byte[] pubkey = diffieHellman.PublicKey.ToByteArray();

            while (run)
            {
                try
                {
                    if (!run) { break; }
                    //IZMENJAVA KLJUCEV
                    TcpClient client = server.AcceptTcpClient();
                    NetworkStream ns = client.GetStream();

                    byte[] data = Receive(ns);
                    if (!run) { break; }
                    //richTextBox1.Text += "Prejel javni kljuc: " + Convert.ToBase64String(data) + "\n";
                    richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Prejel javni kljuc: " + Convert.ToBase64String(data) + "\n"));

                    Send(ns, pubkey);
                    //richTextBox1.Text += "Poslal javni kljuc: " + Convert.ToBase64String(pubkey) + "\n";
                    richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Poslal javni kljuc: " + Convert.ToBase64String(pubkey) + "\n"));
                    byte[] iv = Receive(ns);
                    //richTextBox1.Text += "Prejel iv: " + Encoding.UTF8.GetString(iv) + "\n";

                    byte[] key = diffieHellman.DeriveKeyMaterial(ECDiffieHellmanCngPublicKey.FromByteArray(data, CngKeyBlobFormat.EccPublicBlob));
                    //richTextBox1.Text += "Ustvaril key\n";

                    //PRENOS SIFRIRANIH PODATKOV

                    byte[] msg = Receive(ns);

                    richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Prejel sporocilo\n"));
                    string decrypted = Encoding.UTF8.GetString(Decrypt(msg, key, iv));


                    string[] split = decrypted.Split('|');

                    richTextBox1.Invoke(new Action(() => richTextBox1.Text += split[0] + "|" + split[1] + "\n"));

                    int repeats = Convert.ToInt32(split[1]);
                    
                    FileStream fs = File.Create("C:\\Users\\simon\\source\\repos\\HibridnoSifriranje\\Datoteke\\"+ split[0]);

                    
                    for (int i = 0; i < repeats; i++)
                    {
                        msg = Receive(ns);
                        byte[] decr = Decrypt(msg, key, iv);
                        fs.Write(decr);
                    }

                    richTextBox1.Invoke(new Action(() => richTextBox1.Text += "Datoteka shranjena\n"));
                    
                    fs.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Napaka!\n" + ex.Message + "\n" + ex.StackTrace);
                }
            }
            server.Stop();
            serverThread.Join();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            //Select File

            OpenFileDialog odf = new OpenFileDialog();
            if (odf.ShowDialog() == DialogResult.OK)
            {
                filePath = odf.FileName;
                richTextBox1.Text += "Izbrana datoteka: " + filePath + "\n";
            }
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            //Client
            //Sender();

            clientThread = new Thread(Sender);
            try
            {
                clientThread.Start();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Napaka pri klientu!\n" + ex.Message + "\n" + ex.StackTrace);
            }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            //Server
            run = true;
            serverThread = new Thread(Receiver);
            try
            {
                serverThread.Start();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Napaka pri serverju!\n" + ex.Message + "\n" + ex.StackTrace);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            run = false;
        }
    }
}
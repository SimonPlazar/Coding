//SERVER
using System;
using System.ComponentModel;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;

namespace WebChat_Server
{
    public class Server
    {
        #region Konstante
        const int STD_PORT = 1234;
        const string STD_IP = "127.0.0.1";
        const int STD_MSG_SIZE = 1024;
        const int STD_HEAD_LEN = 1;
        const string STD_CRYPTO_KEY = "mojKljuč";

        static bool run = true;

        static List<(NetworkStream, string)> CLIENTS = new List<(NetworkStream, string)>();
        #endregion

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

        public static void BroadcastMessage(string message)
        {   
            foreach((NetworkStream, string) CLIENT in CLIENTS) 
                Send(CLIENT.Item1, message);
        }

        public static void UserSendMessage(NetworkStream ns, string message)
        {
            foreach ((NetworkStream, string) CLIENT in CLIENTS)
            {
                if (CLIENT.Item1 == ns)
                {
                    BroadcastMessage(CLIENT.Item2 + ": " +  message);
                    return;
                }
            }
        }

        public static void Disconnect(NetworkStream ns)
        {
            foreach ((NetworkStream, string) CLIENT in CLIENTS)
            {
                if (CLIENT.Item1 == ns)
                {
                    CLIENTS.Remove(CLIENT);

                    BroadcastMessage((CLIENT.Item2 + " je zapustil klepet."));

                    CLIENT.Item1.Close();
                    
                    
                    
                    return;
                }
            }
        }

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

        public static void Protokol(NetworkStream ns, string message = "")
        {
            if(message == "")
                message = Receive(ns);

            if (message != "" && message != null) { 

                message = Decrypt(message);

                string[] subs = { };

                if (message != null)
                    subs = message.Split('|');

                string body = "";

                string head = subs[0];

                if (subs.Length > 1)
                {
                    for (int i = 1; i<subs.Length; i++)
                    {
                        body += i + 1 != subs.Length? subs[i] + '|' : subs[i];
                    }
                }
            
                switch (head)
                {
                    case "J":
                        CLIENTS.Add((ns, body));
                        BroadcastMessage((body + " se je pridruzil klepetu."));
                        Console.WriteLine(message);
                        break;
                    case "M":
                        Console.WriteLine(message + " -> client:" + CLIENTS.Find(Client => Client.Item1 == ns).Item2);
                        UserSendMessage(ns, (body));
                        break;
                    case "L":
                        Console.WriteLine(message + " -> client:" + CLIENTS.Find(Client => Client.Item1 == ns).Item2);
                        Disconnect(ns);
                        run = false;
                        break;
                    default:
                        Send(ns, ("Napacna izbira"));
                       break;
                }

                while (run)
                {
                    string msg = Receive(ns);
                    Protokol(ns, msg);
                }
                
            }
        }

        static void Main(string[] args)
        {
            TcpListener listener = new TcpListener(IPAddress.Parse(STD_IP), STD_PORT);
            listener.Start();

            Console.WriteLine("Strežnik\n poslušam na naslovu " + STD_IP + ":" + STD_PORT.ToString());
            
            while (run)
            {
                try
                {
                    TcpClient client = listener.AcceptTcpClient();
                    NetworkStream ns = client.GetStream();

                    Thread newThread = new Thread(() => Protokol(ns));
                    try {
                        newThread.Start();

                    } catch (Exception e) {
                        Console.WriteLine("Napaka!\n" + e.Message + "\n" + e.StackTrace);
                        newThread.Join();
                    }

                }
                catch (Exception ex) 
                {
                    Console.WriteLine("Napaka pri pošiljatelju!\n" + ex.Message + "\n" + ex.StackTrace);
                }

            }


            listener.Stop();
            Console.WriteLine("Strežnik se je ustavil");
            Console.ReadKey();
        }
    }
}
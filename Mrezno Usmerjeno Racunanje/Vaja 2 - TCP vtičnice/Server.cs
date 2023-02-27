//SERVER
using System;
using System.ComponentModel;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;



namespace server
{
    public class Program
    {
        #region Konstante
        const int STD_PORT = 1234;
        const string STD_IP = "127.0.0.1";
        const int STD_MSG_SIZE = 1024;
        const int STD_HEAD_LEN = 1;
        const string STD_CRYPTO_KEY = "mojKljuč";

        static bool run = true;
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

        static string ForsythEdwards(string msg) {
            string formated = "";
            int numeric;
            int spaces = 0;
            int j;

            for (int i = 0; i < msg.Length; i++)
            {
                if (msg[i] == ' ') { 
                    spaces++;
                    formated += "\n";
                    continue;
                }

                switch (spaces)
                {
                    case 0:
                        if (msg[i] == '/')
                        {
                            formated += "\n";
                            continue;
                        }
                        if (Char.IsDigit(msg[i]))
                        {
                            numeric = (int)char.GetNumericValue(msg[i]);
                            for (int k = 0; k < numeric; k++) formated += " ";
                            continue;
                        }
                        formated += msg[i];
                        break;

                    case 1:
                        formated += msg[i] == 'w' ? "Active color: White\n" : "Active color: Black\n";
                        continue;
                        break;

                    case 2:
                        if (msg[i] == 'k')
                        {
                            formated += "Black can castle kingside\n";
                            continue;
                        }
                        if (msg[i] == 'K')
                        {
                            formated += "White can castle kingside\n";
                            continue;
                        }
                        if (msg[i] == 'q')
                        {
                            formated += "Black can castle queenside\n";
                            continue;
                        }
                        if (msg[i] == 'Q')
                        {
                            formated += "White can castle queenside\n";
                            continue;
                        }
                        if (msg[i] == '-')
                        {
                            formated += "Neither side has the ability to castle\n";
                            continue;
                        }
                        break;

                    case 3:
                        if (msg[i] == '-')
                        {
                            formated += "There is no en passant target square\n";
                            continue;
                        }

                        formated += "en passant target" + msg[i] + msg[i+1];
                        i++;
                        continue;
                        break;

                    case 4:
                        formated += "Halfmove clock: ";
                       
                        for (j = 0; msg[i + j] != ' '; j++) {
                            formated += msg[i + j];
                        }
                        i += j - 1;
                        formated += "\n";
                        continue;
                        break;

                    case 5:
                        formated += "Fullmove number: ";
                        for (j = 0; i + j < msg.Length; j++)
                        {
                            formated += msg[i + j];
                        }
                        i += j;
                        formated += "\n";
                        break;
                }
            }
            return formated;
        }

        public static string Encrypt(string message)
        {
            //https://stackoverflow.com/questions/4100996/c-sharp-encoding-in-des-encryption-decryption
            //Pretvori sporočilo in geslo v byte
            byte[] messageBytes = ASCIIEncoding.ASCII.GetBytes(message);
            byte[] passwordBytes = ASCIIEncoding.ASCII.GetBytes(STD_CRYPTO_KEY);

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

        static void Main(string[] args)
        {
            TcpListener listener = new TcpListener(IPAddress.Parse(STD_IP), STD_PORT);
            listener.Start();

            Console.WriteLine("Strežnik\n poslušam na naslovu " + STD_IP + ":" + STD_PORT.ToString());
            while (run)
            {
                TcpClient client = listener.AcceptTcpClient();
                using (NetworkStream ns = client.GetStream())
                {
                    Console.WriteLine("Odjemalec se je povezal (" + client.Client.RemoteEndPoint.ToString() + ")");

                    string message = Receive(ns);

                    Console.WriteLine("Dobil sem sporočilo: " + message);
                    string response = "";

                    string[] subs = message.Split('|');

                    string body = "";

                    string head = subs[0];

                    if (subs.Length > 1) {
                        for (int i = 1; i < subs.Length; i++) {
                            body += i + 1 != subs.Length ? subs[i] + '|' : subs[i];
                        }
                    }

                    switch (head)
                    {
                        case "A":
                            response = "Pozdravljen " + client.Client.RemoteEndPoint.ToString();
                            break;
                        case "B":
                            response = "Trenutni čas je: " + DateTime.Now.ToString("dd. MM. yyyy, H:mm");
                            break;
                        case "C":
                            response = Environment.CurrentDirectory;
                            break;
                        case "D":
                            response = body;
                            break;
                        case "E":
                            response = Environment.MachineName + "\n" + Environment.OSVersion.ToString;
                            break;
                        case "F":
                            response = ForsythEdwards(body);
                            break;
                        case "G":
                            response = Encrypt(body);
                            break;
                        default:
                            response = "Napacna izbira";
                            break;
                            
                    }

                    Send(ns, response);
                    Console.WriteLine("Odgovoril sem: " + response);

                }
                Console.WriteLine("Odjemalec se je odklopil\n");


            }
            listener.Stop();
            Console.WriteLine("Strežnik se je ustavil");
            Console.ReadKey();
        }
    }
}
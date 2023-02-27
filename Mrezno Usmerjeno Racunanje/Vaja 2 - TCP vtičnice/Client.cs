
using System;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;

namespace client
{
    class Program
    {
        #region Konstante
        const int STD_PORT = 1234; //standardni port na katerem bomo komunicirali
        const string STD_IP = "127.0.0.1";//local host
        const int STD_MSG_SIZE = 1024;//konstanta za velikost paketa (1KB)
        const int STD_HEAD_LEN = 1; //glava pa bo velika en bajt
        const string STD_CRYPTO_KEY = "mojKljuč";//zašifriramo
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
                Console.WriteLine("Napaka pri prejemniku!n" + ex.Message + "\n" + ex.StackTrace);
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
                Console.WriteLine("Napaka pri pošiljatelju!n" + ex.Message + "\n" + ex.StackTrace);
            }
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

        static void Main(string[] args)
        {
            Console.Write("Odjemalec");
            while (true)
            {
                Console.Write("\nVnesi ukaz: ");
                string console_input = Console.ReadLine();

                if (console_input == "q") break;

                try
                {
                    TcpClient client = new TcpClient();
                    client.Connect(STD_IP, STD_PORT);

                    NetworkStream ns = client.GetStream();
                    Send(ns, console_input);
                    string response = Receive(ns);

                    if (console_input[0] == 'G')
                    {
                        response += " => " + Decrypt(response);
                    }

                    Console.WriteLine("Strežnik vrača: \n" + response);

                }
                catch (Exception ex)
                {
                    Console.WriteLine("Napaka: " + ex.Message + "\n" + ex.StackTrace);
                }
            }

            Console.WriteLine("Pritisni poljubno tipko za zaključek programa");
            Console.ReadKey();
        }

    }
}

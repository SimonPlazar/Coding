namespace Blockchain
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            var thread = new Thread(ThreadStart);
            thread.TrySetApartmentState(ApartmentState.STA);
            thread.Start();

            var thread2 = new Thread(ThreadStart);
            thread2.TrySetApartmentState(ApartmentState.STA);
            thread2.Start();

            Application.Run(new Form1());
        }
        private static void ThreadStart()
        {
            Application.Run(new Form1()); // <-- other form started on its own UI thread
        }
    }
}
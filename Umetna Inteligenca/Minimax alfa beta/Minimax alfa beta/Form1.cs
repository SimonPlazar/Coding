using Microsoft.VisualBasic.Devices;
using System.Media;
using System.Security.Cryptography.X509Certificates;
using static System.Windows.Forms.LinkLabel;

namespace Minimax_alfa_beta
{
    public partial class Form1 : Form
    {
        Point cursor;
        Graphics g;
        Pen penBlack;
        Pen penRed;
        Pen penBlue;

        int PointHeight = 75;
        int PointWidth = 75;

        bool player;

        string[] Depths = new string[]
                {
                    "Depth: 1",
                    "Depth: 2",
                    "Depth: 3",
                    "Depth: 4",
                    "Depth: 5",
                    "Depth: 6",
                    "Depth: 7",
                    "Depth: 8"
                };

        int depth = -1;

        int[] Board = new int[]
                {
                    0, 0, 0,
                    0, 0, 0,
                    0, 0, 0
                };

        List<Point> Centers = new List<Point>
                {
                    new Point(270, 95), new Point(400, 95), new Point(530, 95),
                    new Point(270, 225), new Point(400, 225), new Point(530, 225),
                    new Point(270, 355), new Point(400, 355), new Point(530, 355),
                };

        public Form1()
        {
            InitializeComponent();

            g = this.CreateGraphics();

            penBlack = new Pen(Color.Black, 5);
            penRed = new Pen(Color.Red, 5);
            penBlue = new Pen(Color.Blue, 5);

            DepthSelect.Items.AddRange(Depths);

            player = false;
            
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            //update pos
            cursor = this.PointToClient(Cursor.Position);
            MouseLocation.Text = "X: " + cursor.X + " Y: " + cursor.Y;
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            g.DrawLine(penBlack, 595, 30, 595, 420);
            g.DrawLine(penBlack, 465, 30, 465, 420);
            g.DrawLine(penBlack, 335, 30, 335, 420);
            g.DrawLine(penBlack, 205, 30, 205, 420);

            g.DrawLine(penBlack, 205, 420, 595, 420);
            g.DrawLine(penBlack, 205, 290, 595, 290);
            g.DrawLine(penBlack, 205, 160, 595, 160);
            g.DrawLine(penBlack, 205, 30, 595, 30);
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            if (depth == -1) return; // selectan depth

            if (chechEndGame(Board)) return;

            int pos = GetPos(e);

            if (pos == -1) return; //ce klik ni na igralnem polju

            if (Board[pos] != 0) return; // ce je ze zapolnjeno polje

            DrawPoint(pos);

            if (chechEndGame(Board))
            {
                Winner.Text = "Winner: Krogec";
            }
            else if (!Board.Contains(0))
            {
                Winner.Text = "Winner: Draw";
            }

            var result = Minimax(player, depth + 1, -10000, +10000, Board);

            if (result[1] == -1) 
            { 
                Console.Write("Error minnimax move -1:" + result[1]);
                return;
            }

            DrawPoint(result[1]);

            if (chechEndGame(Board))
            {
                Winner.Text = "Winner: Krizec";
            }
            else if (!Board.Contains(0))
            {
                Winner.Text = "Winner: Draw";
            }
        }

        List<int> Minimax(bool player, int depth, int alfa, int beta, int[] board)
        {
            if (depth == 0 || chechEndGame(board) || !Board.Contains(0))
                return new List<int>() { hevristika(board, player), -1 };

            int evaluation;

            if (player) evaluation = -100;
            else evaluation = 100;

            int move = -1;

            List<int> result;
            int[] tempBoard = new int[9];
            
            var possibleMoves = moves(board);

            foreach (int possibleMove in possibleMoves)
            {
                board.CopyTo(tempBoard, 0);

                if (player) tempBoard[possibleMove] = 2;
                else tempBoard[possibleMove] = 1;

                result = Minimax(!player, depth - 1, alfa, beta, tempBoard);
                if (player && (result[0] > evaluation))
                {
                    evaluation = result[0];
                    move = possibleMove;
                    alfa = Math.Max(alfa, evaluation);
                }
                else if(!player && (result[0] < evaluation))
                {
                    evaluation = result[0];
                    move = possibleMove;
                    beta = Math.Min(beta, evaluation);
                }

                if (alfa >= beta) return new List<int>() { evaluation, move };
            }
            return new List<int>() { evaluation, move };
        }

        /*
        List<int> Minimax(bool player, int depth, int alfa, int beta, int[] board)
        {
            if (depth == 0 || chechEndGame(board) || !Board.Contains(0))
                return new List<int>() { hevristika(board, player), -1 };

            var possibleMoves = moves(board);
            var move = -1;
            var tmpBoard = new int[9];

            if (player) //max
            {
                var val = -100;
                foreach (var possibleMove in possibleMoves)
                {
                    board.CopyTo(tmpBoard, 0);
                    tmpBoard[possibleMove] = 2;

                    var result = Minimax(!player, depth - 1, alfa, beta, tmpBoard);

                    if (val < result[0])
                    {
                        val = result[0];
                        alfa = Math.Max(alfa, val);
                        move = possibleMove;
                    }
                    if (val >= beta) break;
                    //
                    val = Math.Max(val, Minimax(!player, depth - 1, alfa, beta, tmpBoard)[0]);
                    alfa = Math.Max(alfa, val);
                    if (val >= beta) break;
                    move = possibleMove;
                    //
                }
                return new List<int>() { val, move };
            }
            else //min
            {
                var val = 100;
                foreach (int possibleMove in possibleMoves)
                {
                    board.CopyTo(tmpBoard, 0);
                    tmpBoard[possibleMove] = 1;

                    var result = Minimax(!player, depth - 1, alfa, beta, tmpBoard);
                    
                    if (val > result[0])
                    {
                        val = result[0];
                        beta = Math.Min(beta, val);
                        move = possibleMove;
                    }
                    if (val <= alfa) break;
                    //
                    val = Math.Min(val, result[0]);
                    beta = Math.Min(beta, val);
                    if (val <= alfa) break;
                    move = possibleMove;
                    //
                }
                return new List<int>() { val, move };
            }
        }
        */

        List<int> moves(int[] board)
        {
            List<int> arr = new List<int> { };

            for (int i = 0; i < 9; i++)
            {
                if (board[i] == 0)
                    arr.Add(i);
            }

            return arr;
        }

        int hevristika(int[] board, bool player)
        {
            int O = 0;
            int X = 0;

            int znak;

            if(player) { znak = 2; }
            else { znak = 1; }

            //rows/cols
            for (int i = 0; i < 3; i++)
            {
                //Row win
                if (board[i * 3 + 0] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2] && board[i * 3 + 2] == znak)
                {
                    
                    if (player) O += 100;
                    else X += 100;
                }
                //row 2
                else if (
                    (board[i * 3 + 0] == board[i * 3 + 1] && board[i * 3 + 1] == znak && board[i * 3 + 2] == 0) || //1x2
                    (board[i * 3 + 1] == board[i * 3 + 2] && board[i * 3 + 2] == znak && board[i * 3 + 0] == 0) || //2x3
                    (board[i * 3 + 0] == board[i * 3 + 2] && board[i * 3 + 2] == znak && board[i * 3 + 1] == 0)    //1x3
                        )   
                {   
                    if (player) O += 10;
                    else X += 10;
                }
                //row 1
                else if (board[i * 3 + 0] == znak || board[i * 3 + 1] == znak || board[i * 3 + 2] == znak)
                {
                    if (player) O += 1;
                    else X += 1;
                }
                //Column win
                if (board[i + 0] == board[i + 3] && board[i + 3] == board[i + 6] && board[i + 6] == znak)
                {
                    if (player) O += 100;
                    else X += 100;
                }
                //col 2
                else if (
                    (board[i + 0] == board[i + 3] && board[i + 3] != 0 && board[i + 6] == 0) || //1x2
                    (board[i + 3] == board[i + 6] && board[i + 6] != 0 && board[i + 0] == 0) || //2x3
                    (board[i + 0] == board[i + 6] && board[i + 6] != 0 && board[i + 3] == 0)    //1x3
                        )   
                {   
                    if (player) O += 10;
                    else X += 10;
                }
                //col 1
                else if (board[i + 0] == znak || board[i + 3] == znak || board[i + 6] == znak)
                {
                    if (player) O += 1;
                    else X += 1;
                }
            }

            //Diag 1 win
            if (board[0] == board[4] && board[4] == board[8] && board[8] == znak)
            {
                if (player) O += 100;
                else X += 100;
            }
            //Diag 1 2
            else if (
                (board[0] == board[4] && board[4] == znak && board[8] == 0) || //1x2
                (board[4] == board[8] && board[8] == znak && board[0] == 0) || //2x3
                (board[0] == board[8] && board[8] == znak && board[4] == 0)    //1x3
                    )
            {
                if (player) O += 10;
                else X += 10;
            }
            //Diag 1 1
            else if (board[0] == znak || board[4] == znak || board[8] == znak)
            {
                if (player) O += 1;
                else X += 1;
            }

            //Diag 2 win
            if (board[2] == board[4] && board[4] == board[6] && board[6] == znak)
            {
                if (player) O += 100;
                else X += 100;
            }
            //Diag 2 2
            else if (
                (board[2] == board[4] && board[4] == znak && board[6] == 0) || //1x2
                (board[4] == board[6] && board[6] == znak && board[2] == 0) || //2x3
                (board[2] == board[6] && board[6] == znak && board[4] == 0)    //1x3
                    )
            {
                if (player) O += 10;
                else X += 10;
            }
            //Diag 2 1
            else if (board[2] == znak || board[4] == znak || board[6] == znak)
            {
                if (player) O += 1;
                else X += 1;
            }

            if(!player) return X - O; 
            return O - X; 
        }

        bool chechEndGame(int[] board)
        {
            for (int i = 0; i < 3; i++)
            {
                if (board[i * 3 + 0] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2] && board[i * 3 + 2] != 0)
                {
                    //Row win
                    return true;
                }
                else if (board[i + 0] == board[i + 3] && board[i + 3] == board[i + 6] && board[i + 6] != 0)
                {
                    //Column win
                    return true;
                }
            }

            if (board[0] == board[4] && board[4] == board[8] && board[8] != 0)
            {
                //Diag win
                return true;
            }
            else if (board[2] == board[4] && board[4] == board[6] && board[6] != 0)
            {
                //Diag win
                return true;
            }
            /*
            if (!board.Contains(0))
            {
                return true;
            }
            */

            return false;
        }

        void ClearBoard()
        {
            for (int i = 0; i < 9; i++)
            {
                if (Board[i] != 0) Board[i] = 0;
            }

            g.Clear(Control.DefaultBackColor);
            player = false;
            Winner.Text = "Winner: -";
        }

        void DrawPoint(int pos)
        {
            if (!player) 
            {
                g.DrawEllipse(penRed, Centers[pos].X - PointHeight / 2, Centers[pos].Y - PointWidth / 2, PointHeight, PointWidth);
                Board[pos] = 1;
            }
            else
            {
                Board[pos] = 2;
                g.DrawLine(penBlue, Centers[pos].X - PointHeight / 2, Centers[pos].Y - PointWidth / 2, Centers[pos].X + PointHeight / 2, Centers[pos].Y + PointWidth / 2);
                g.DrawLine(penBlue, Centers[pos].X + PointHeight / 2, Centers[pos].Y - PointWidth / 2, Centers[pos].X - PointHeight / 2, Centers[pos].Y + PointWidth / 2);
            }
            player = !player;
        }

        int GetPos(MouseEventArgs e)
        {
            var X = e.Location.X;
            var Y = e.Location.Y;

            if (X > 205 && X < 335) // First Col
            {
                if (Y > 30 && Y < 160) // First Row
                    return 0;
                else if (Y > 160 && Y < 290)
                    return 3;
                else if (Y > 290 && Y < 420)
                    return 6;
            }
            else if (X > 335 && X < 465)
            {
                if (Y > 30 && Y < 160)
                    return 1;
                else if (Y > 160 && Y < 290)
                    return 4;
                else if (Y > 290 && Y < 420)
                    return 7;
            }
            else if (X > 465 && X < 595)
            {
                if (Y > 30 && Y < 160)
                    return 2;
                else if (Y > 160 && Y < 290)
                    return 5;
                else if (Y > 290 && Y < 420)
                    return 8;
            }

            return -1;
        }

        private void DepthSelect_SelectedIndexChanged(object sender, EventArgs e)
        {
            depth = DepthSelect.SelectedIndex;
        }

        private void ClearBtn_Click(object sender, EventArgs e)
        {
            ClearBoard();
        }
    }
}
using System.Drawing.Drawing2D;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Security.Cryptography.Pkcs;
using System.Security.Cryptography.Xml;
using static System.Windows.Forms.LinkLabel;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TrackBar;

namespace RGEO_vaja1
{

    public partial class Form1 : Form
    {
        private const int PointHeight = 5;
        private const int PointWidth = 5;
        Point cursor;
        Graphics g;
        Pen penRed;
        Pen penBlue;
        Pen penGreen;

        List<Point> Points;
        List<List<Point>> Lines;

        bool LinePoint = false;

        int PointCount = 0;
        int LineCount = 0;

        string[] Modes = new string[]
                { "Tocka-Tocka",
                  "Tocka-Daljica",
                  "Daljica-Daljica"
                };

        List<List<int>> Meje = new List<List<int>>()
                { 
                  // PointCount, LineCount
                  new List<int>(){2, 0},
                  new List<int>(){1, 1},
                  new List<int>(){0, 2}
                };

        public Form1()
        {
            InitializeComponent();

            g = this.CreateGraphics();

            penRed = new Pen(Color.Red, 5);
            penBlue = new Pen(Color.Blue, 5);
            penGreen = new Pen(Color.Green, 5);

            Points = new List<Point>();
            Lines = new List<List<Point>>();

            CordList.Text = "Cords List: \n";
            ModeSelect.Items.AddRange(Modes);
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            //update pos
            cursor = this.PointToClient(Cursor.Position);
            MouseLocation.Text = "X: " + cursor.X + " Y: " + cursor.Y;
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            if (ModeSelect.SelectedIndex == -1)
                return;

            if (e.Button == MouseButtons.Right)
            {
                //line
                CreateLine(cursor.X, cursor.Y);
            }
            else if (e.Button == MouseButtons.Left)
            {
                CreatePoint(cursor.X, cursor.Y);
            }
        }

        void CreateLine(int X, int Y)
        {
            if (LineCount >= Meje[ModeSelect.SelectedIndex][1])
                return;

            if (!LinePoint)
            {
                g.DrawEllipse(penBlue, X - (PointHeight / 2), Y - (PointHeight / 2), PointWidth, PointHeight);
                Lines.Add(new List<Point>());
                Lines[Lines.Count - 1].Add(new Point(X, Y));
                LinePoint = true;
            }
            else
            {
                g.DrawEllipse(penBlue, X - (PointHeight / 2), Y - (PointHeight / 2), PointWidth, PointHeight);
                Lines[Lines.Count - 1].Add(new Point(X, Y));

                g.DrawLine(penBlue, Lines[Lines.Count - 1][0], Lines[Lines.Count - 1][1]);
                CordList.Text += "Line: (" +
                    Lines[Lines.Count - 1][0].X + ", " +
                    Lines[Lines.Count - 1][0].Y + ") -> (" +
                    Lines[Lines.Count - 1][1].X + ", " +
                    Lines[Lines.Count - 1][1].Y + ")\n";

                LinePoint = false;
                LineCount++;
            }
        }

        void CreatePoint(int X, int Y)
        {
            if (PointCount >= Meje[ModeSelect.SelectedIndex][0])
                return;

            Points.Add(new Point(X, Y));
            g.DrawEllipse(penRed, X - (PointHeight / 2), Y - (PointHeight / 2), PointWidth, PointHeight);
            CordList.Text += "Point: (" + X + ", " + Y + ")\n";
            PointCount++;
        }

        private void Clear_Click(object sender, EventArgs e)
        {
            Points.Clear();
            Lines.Clear();
            g.Clear(Control.DefaultBackColor);
            CordList.Text = "Cords List: \n";
            PointCount = 0;
            LineCount = 0;
        }

        private void Calculate_Click(object sender, EventArgs e)
        {
            if (ModeSelect.SelectedIndex == -1)
                return;

            if (LineCount < Meje[ModeSelect.SelectedIndex][1])
                return;

            if (PointCount < Meje[ModeSelect.SelectedIndex][0])
                return;

            switch (ModeSelect.SelectedIndex)
            {
                case -1:
                    return;

                case 0:
                    TockaTocka();
                    break;

                case 1:
                    TockaDaljica();
                    break;

                case 2:
                    DaljicaDaljica();
                    break;
            }
        }

        void TockaTocka()
        {
            float EuclidDistance = euclidDistace(Points[0], Points[1]);

            float ManhattanDistance = (float)Math.Abs(Points[0].X - Points[1].X) +
                                      (float)Math.Abs(Points[0].Y - Points[1].Y);

            float ChebyshevDistance = Math.Max(
                            (float)Math.Abs(Points[0].X - Points[1].X),
                            (float)Math.Abs(Points[0].Y - Points[1].Y)
                            );

            CordList.Text += "Euclid Distance: " + EuclidDistance + "\n" +
                             "Manhattan Distance: " + ManhattanDistance + "\n" +
                             "Chebyshev Distance: " + ChebyshevDistance + "\n";

            g.DrawLine(penGreen, Points[0], Points[1]);
        }

        void TockaDaljica()
        {

            var rt1 = new Vector2(Points[0].X, Points[0].Y);
            var rt2 = new Vector2(Lines[0][0].X, Lines[0][0].Y);
            var rt3 = new Vector2(Lines[0][1].X, Lines[0][1].Y);

            var v1 = Vector2.Add(rt3, Vector2.Negate(rt2));
            var v2 = Vector2.Add(rt1, Vector2.Negate(rt2));

            var vn = Vector2.Normalize(v1);

            float sp = Vector2.Dot(vn, v2);

            var tp = Vector2.Add(rt2, Vector2.Multiply(vn, sp));

            if (0 < sp && sp < v1.Length())
            {
                g.DrawEllipse(penRed, tp.X - (PointHeight / 2), tp.Y - (PointHeight / 2), PointWidth, PointHeight);
                g.DrawLine(penGreen, tp.X, tp.Y, Points[0].X, Points[0].Y);
                CordList.Text += "Dolzina T1->Tp: " + euclidDistace(Points[0].X, Points[0].Y, tp.X, tp.Y);
                return;
            }
            else if (0 > sp)
            {
                g.DrawLine(penGreen, Lines[0][0], Points[0]);
                CordList.Text += "Dolzina T1->T2: " + euclidDistace(Points[0], Lines[0][0]);
            }
            else
            {
                g.DrawLine(penGreen, Lines[0][1], Points[0]);
                CordList.Text += "Dolzina T1->T3: " + euclidDistace(Points[0], Lines[0][1]);
            }

            var xd = v2.X * v1.Y - v1.X * v2.Y;
            if (xd > 0) CordList.Text += "\nTocka se nahaja na levi strani daljice!\n";
            if (xd < 0) CordList.Text += "\nTocka se nahaja na desni strani daljice!\n";


        }

        void DaljicaDaljica()
        {
            var rt1 = new Vector2(Lines[0][0].X, Lines[0][0].Y);
            var rt2 = new Vector2(Lines[0][1].X, Lines[0][1].Y);
            var rt3 = new Vector2(Lines[1][0].X, Lines[1][0].Y);

            var v1 = Vector2.Add(rt2, Vector2.Negate(rt1));
            var v2 = Vector2.Add(rt3, Vector2.Negate(rt1));

            var xd = v1.X * v2.Y - v2.X * v1.Y;

            if (xd == 0)
            {
                CordList.Text += "Vzporedni daljici!\n";
                return;
            }

            float D = (Lines[0][1].X - Lines[0][0].X) * (Lines[1][1].Y - Lines[1][0].Y) -
                (Lines[1][1].X - Lines[1][0].X) * (Lines[0][1].Y - Lines[0][0].Y);

            float A = (Lines[1][1].X - Lines[1][0].X) * (Lines[0][0].Y - Lines[1][0].Y) -
                (Lines[0][0].X - Lines[1][0].X) * (Lines[1][1].Y - Lines[1][0].Y);

            float B = (Lines[0][1].X - Lines[0][0].X) * (Lines[0][0].Y - Lines[1][0].Y) -
                (Lines[0][0].X - Lines[1][0].X) * (Lines[0][1].Y - Lines[0][0].Y);

            if (D == A && A == B && B == 0)
            {
                CordList.Text += "Daljici sovpadata!\n";

                List<Point> sorted = new List<Point>() {
                    Lines[0][0],
                    Lines[0][1],
                    Lines[1][0],
                    Lines[1][1]
                };

                sorted = sortListPoints(sorted);

                CordList.Text += "Odsek sovpadanja:\n" + sorted[1] + "->" + sorted[2] + "\n";
                g.DrawEllipse(penRed, sorted[1].X - (PointHeight / 2), sorted[1].Y - (PointHeight / 2), PointWidth, PointHeight);
                g.DrawEllipse(penRed, sorted[2].X - (PointHeight / 2), sorted[2].Y - (PointHeight / 2), PointWidth, PointHeight);
                g.DrawLine(penGreen, sorted[1], sorted[2]);

                return;
            }

            if (D == 0)
                CordList.Text += "Vzporedni daljici!\n";

            float Ua = (float)(A / D);
            float Ub = (float)(B / D);

            if (0 == Ua)
            {
                CordList.Text += "Daljici se dotikata v tocki T1\n" + Lines[0][0] + "\n";
            }
            else if (0 == Ub)
            {
                CordList.Text += "Daljici se dotikata v tocki T3\n" + Lines[1][0] + "\n";
            }
            else if (1 == Ua)
            {
                CordList.Text += "Daljici se dotikata v tocki T2\n" + Lines[0][1] + "\n";
            }
            else if (1 == Ub)
            {
                CordList.Text += "Daljici se dotikata v tocki T4\n" + Lines[1][1] + "\n";
            }
            else if ((0 < Ua && Ua < 1) && (0 < Ub && Ub < 1))
            {
                float x1 = Lines[0][0].X + Ua * (Lines[0][1].X - Lines[0][0].X);
                float x2 = Lines[1][0].X + Ub * (Lines[1][1].X - Lines[1][0].X);

                float y1 = Lines[0][0].Y + Ua * (Lines[0][1].Y - Lines[0][0].Y);
                float y2 = Lines[1][0].Y + Ub * (Lines[1][1].Y - Lines[1][0].Y);

                float x = (x1 + x2) / 2;
                float y = (y1 + y2) / 2;

                CordList.Text += "Daljicise sekata:\nx: " + x + "\ny: " + y + "\n";
                g.DrawEllipse(penRed, x - (PointHeight / 2), y - (PointHeight / 2), PointWidth, PointHeight);
            }
            else
            {
                CordList.Text += "Daljici se ne sekata\n";
            }
        }

        List<Point> sortListPoints(List<Point> list)
        {
            Point tmp = new Point();
            //Bubble sort
            for (int i = 0; i < 4 - 1; i++)
            {
                for (int j = 0; j < 4 - i - 1; j++)
                {
                    if (!IsPointLarger(list[j], list[j + 1]))
                    {
                        tmp = list[j];
                        list[j] = list[j + 1];
                        list[j + 1] = tmp;
                    }
                }
            }

            return list;
        }

        bool IsPointLarger(Point P1, Point P2)
        {
            return (P1.X < P2.X || (P1.X == P2.X && P1.Y < P2.Y));
        }

        float euclidDistace(Point p1, Point p2)
        {
            return (float)Math.Sqrt(
                        (float)Math.Pow((p1.X - p2.X), 2) +
                        (float)Math.Pow((p1.Y - p2.Y), 2)
                        );
        }

        float euclidDistace(float x1, float y1, float x2, float y2)
        {
            return (float)Math.Sqrt(
                        (float)Math.Pow((x1 - x2), 2) +
                        (float)Math.Pow((y1 - y2), 2)
                        );
        }

        private void CreatePointBtn_MouseClick(object sender, MouseEventArgs e)
        {
            if (ModeSelect.SelectedIndex == -1)
                return;

            if (CheckBox.Checked)
            {
                //line
                CreateLine(Int32.Parse(cordX.Text), Int32.Parse(cordY.Text));
            }
            else if (!CheckBox.Checked)
            {
                CreatePoint(Int32.Parse(cordX.Text), Int32.Parse(cordY.Text));
            }
        }
    }
}
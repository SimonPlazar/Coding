using System.Security.Cryptography;
using Microsoft.VisualBasic.Devices;
using System.Windows.Forms;
using static System.Windows.Forms.LinkLabel;
using System.Numerics;
using System.Drawing;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Rebar;
using System;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace RGEO_vaja2
{
    public partial class Form1 : Form
    {
        private const int PointHeight = 5;
        private const int PointWidth = 5;

        private const int MinX = 12;
        private const int MaxX = 700;

        private const int MinY = 12;
        private const int MaxY = 600;

        private const float CenterX = (MaxX - MinX) / 2;
        private const float CenterY = (MaxY - MinY) / 2;

        private const float stdDev = 75f;

        Point cursor;
        Graphics g;
        Pen penRed;
        Pen penGreen;
        Pen penBlue;

        Random rnd = new Random(Guid.NewGuid().GetHashCode());

        List<Point> Points;

        bool calculated = false;

        string[] DistModes = new string[]
        {
            "Uniform",
            "Normal/Gauss"
        };

        string[] AlgModes = new string[]
        {
            "Jarvis's march",
            "Graham's scan",
            "QuickHull"
        };

        public Form1()
        {
            InitializeComponent();

            g = this.CreateGraphics();

            penRed = new Pen(Color.Red, 5);
            penGreen = new Pen(Color.Green, 5);
            penBlue = new Pen(Color.Blue, 5);

            Points = new List<Point>();

            DistModeSelect.Items.AddRange(DistModes);
            AlgModeSelect.Items.AddRange(AlgModes);
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            //update pos
            cursor = this.PointToClient(Cursor.Position);
            MouseLocation.Text = "X: " + cursor.X + " Y: " + cursor.Y;
        }

        private void GenerateBtn_Click(object sender, EventArgs e)
        {
            if (DistModeSelect.SelectedIndex == -1)
                return;

            if (PointNum.Text == "")
                return;

            Clear();

            int numOfPoints = Convert.ToInt32(PointNum.Text);

            switch (DistModeSelect.SelectedIndex)
            {
                case 0:
                    UniformDistGen(numOfPoints);
                    break;

                case 1:
                    NormalDistGen(numOfPoints);
                    break;

                default:
                    return;
            }
        }

        private void UniformDistGen(int numOfPoints)
        {
            int x, y;
            for (int i = 0; i < numOfPoints; i++)
            {
                //do
                //{
                    x = rnd.Next(MinX, MaxX);
                    y = rnd.Next(MinY, MaxY);
                //} while (Points.Find(point => (point.X == x && point.Y == y)) != default);

                Points.Add(new Point(x, y));
                g.DrawEllipse(penRed, x - (PointHeight / 2), y - (PointHeight / 2), PointWidth, PointHeight);
            }
        }

        private void NormalDistGen(int numOfPoints)
        {
            int x, y;
            double u1, u2, randStdNormal;
            for (int i = 0; i < numOfPoints; i++)
            {
                //do
                //{
                    do
                    {
                        u1 = rnd.NextDouble();
                        u2 = rnd.NextDouble();
                        randStdNormal = Math.Sqrt(-2.0 * Math.Log(u1)) * Math.Sin(2.0 * Math.PI * u2);
                        x = (int)Math.Round(CenterX + stdDev * randStdNormal);
                    } while (MinX > x || x > MaxX);

                    do
                    {
                        u1 = rnd.NextDouble();
                        u2 = rnd.NextDouble();
                        randStdNormal = Math.Sqrt(-2.0 * Math.Log(u1)) * Math.Sin(2.0 * Math.PI * u2);
                        y = (int)Math.Round(CenterY + stdDev * randStdNormal);
                    } while (MinY > y || y > MaxY);
                //} while (Points.Find(point => (point.X == x && point.Y == y)) != default);

                Points.Add(new Point(x, y));
                g.DrawEllipse(penRed, x - (PointHeight / 2), y - (PointHeight / 2), PointWidth, PointHeight);
            }
        }

        private void Clear()
        {
            Points.Clear();
            g.Clear(Control.DefaultBackColor);
        }

        private void ClearBtn_Click(object sender, EventArgs e)
        {
            Clear();
        }

        private void CalculateBtn_Click(object sender, EventArgs e)
        {
            if (AlgModeSelect.SelectedIndex == -1)
                return;

            if (calculated)
                return;

            var watch = new System.Diagnostics.Stopwatch();
            List<Point> hull = new List<Point>();

            watch.Start();
            switch (AlgModeSelect.SelectedIndex)
            {
                case 0:
                    hull = JarvisMarch(Points);
                    break;

                case 1:
                    hull = GrahamScan(Points);
                    break;

                case 2:
                    hull = QuickHull(Points);
                    break;

                default:
                    return;
            }
            watch.Stop();

            for (int i = 0; i < hull.Count - 1; i++)
            {
                g.DrawLine(penBlue, hull[i], hull[i + 1]);
            }
            g.DrawLine(penBlue, hull[0], hull.Last());

            foreach (var p in hull)
            {
                g.DrawEllipse(penGreen, p.X - (PointHeight / 2), p.Y - (PointHeight / 2), PointWidth,
                    PointHeight);
            }

            TimeLabel.Text = "Execution Time: " + watch.ElapsedMilliseconds + " ms";
        }

        public static List<Point> JarvisMarch(List<Point> points)
        {
            List<Point> hull = new List<Point>();

            int leftmost = 0;
            for (int i = 1; i < points.Count; i++)
            {
                if (!IsPointLarger(points[i], points[leftmost]))
                {
                    leftmost = i;
                }
            }

            int p = leftmost;
            do
            {
                hull.Add(points[p]);

                int q = (p + 1) % points.Count;
                for (int i = 0; i < points.Count; i++)
                {
                    if (CheckPointSide(points[p], points[i], points[q]) > 0)
                    {
                        q = i;
                    }
                }

                p = q;
            } while (p != leftmost);

            return hull;
        }

        public static List<Point> GrahamScan(List<Point> points)
        {
            Point O = new Point(
                (points[0].X + points[1].X + points[2].X) / 3,
                (points[0].Y + points[1].Y + points[2].Y) / 3
            );

            Point lowestPoint = points[0];
            foreach (var point in points)
            {
                if (IsPointLarger(point, lowestPoint))
                {
                    lowestPoint = point;
                }
            }
            
            points.Remove(lowestPoint);

            points.Sort((p1, p2) =>
            {
                float angle1 = (float)Math.Atan2(p1.Y - lowestPoint.Y, p1.X - lowestPoint.X);
                float angle2 = (float)Math.Atan2(p2.Y - lowestPoint.Y, p2.X - lowestPoint.X);
                return angle1.CompareTo(angle2);
            });
            points.Insert(0, lowestPoint);

            Stack<Point> stack = new Stack<Point>();
            stack.Push(lowestPoint);
            stack.Push(points[1]);
            stack.Push(points[2]);

            for (int i = 2; i < points.Count; i++)
            {
                Point top = stack.Pop();
                while (CheckPointSide(stack.Peek(), top, points[i]) <= 0)
                {
                    top = stack.Pop();
                }
                stack.Push(top);
                stack.Push(points[i]);
            }

            return new List<Point>(stack);
        }
        
        List<Point> QuickHull(List<Point> points)
        {
            List<Point> hull = new List<Point>();

            Point minX = points[0];
            Point maxX = points[0];

            foreach (var p in points)
            {
                if (!IsPointLarger(p, minX))
                {
                    minX = p;
                }

                if (IsPointLarger(p, maxX))
                {
                    maxX = p;
                }
            }

            hull.Add(minX);
            hull.Add(maxX);

            List<Point> left = new List<Point>();
            List<Point> right = new List<Point>();

            foreach (var p in points)
            {
                if (CheckPointSide(minX, maxX, p) > 0)
                {
                    left.Add(p);
                }
                else if (CheckPointSide(minX, maxX, p) < 0)
                {
                    right.Add(p);
                }
            }

            HullSplit(hull, left, minX, maxX);
            HullSplit(hull, right, maxX, minX);

            hull.Sort((p1, p2) =>
            {
                double angle1 = Math.Atan2(p1.Y - minX.Y, p1.X - minX.X);
                double angle2 = Math.Atan2(p2.Y - minX.Y, p2.X - minX.X);
                return angle1.CompareTo(angle2);
            });

            return hull;
        }

        void HullSplit(List<Point> hull, List<Point> points, Point p1, Point p2)
        {
            if (points.Count == 0) return;

            int distance = -1;
            Point farthest = new Point();

            foreach (var p in points)
            {
                int d = LinePointDistance(p1, p2, p);
                if (distance < d)
                {
                    farthest = p;
                    distance = d;
                }
            }

            hull.Add(farthest);

            List<Point> left = new List<Point>();
            List<Point> right = new List<Point>();

            foreach (var p in points)
            {
                if (CheckPointSide(p1, farthest, p) > 0)
                {
                    left.Add(p);
                }
                else if (CheckPointSide(farthest, p2, p) > 0)
                {
                    right.Add(p);
                }
            }

            HullSplit(hull, left, p1, farthest);
            HullSplit(hull, right, farthest, p2);
        }

        static int CheckPointSide(Point a, Point b, Point c)
        {
            // ret > 0 -> left  | clockwise
            // ret < 0 -> right | counter clockwise
            // ret = 0 -> collinear
            return (b.X - a.X) * (c.Y - a.Y) - (c.X - a.X) * (b.Y - a.Y);
        }

        int LinePointDistance(Point a, Point b, Point c)
        {
            return Math.Abs((b.X - a.X) * (a.Y - c.Y) - (a.X - c.X) * (b.Y - a.Y));
        }

        static bool IsPointLarger(Point P1, Point P2)
        {
            return (P1.X < P2.X || (P1.X == P2.X && P1.Y < P2.Y));
        }
    }
}
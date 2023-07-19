using System.Numerics;
using System.Reflection.PortableExecutable;
using System.Windows.Forms.VisualStyles;


namespace RGEO_vaja4
{
    public partial class Form1 : Form
    {
        private const int PointHeight = 5;
        private const int PointWidth = 5;

        private const int MinX = 12;
        private const int MaxX = 600;

        private const int MinY = 12;
        private const int MaxY = 400;

        Point cursor;
        Graphics g;
        Pen penRed;
        Pen penBlue;
        Pen penGreen;

        private bool calculated = true;

        Random rnd = new Random(Guid.NewGuid().GetHashCode());

        private List<Point> Points;

        string[] AlgModes = new string[]
        {
            "Minimalno Utežena",
            "Hamiltonova"
        };

        public Form1()
        {
            InitializeComponent();

            g = this.CreateGraphics();

            penRed = new Pen(Color.Red, 5);
            penBlue = new Pen(Color.Blue, 5);
            penGreen = new Pen(Color.Green, 5);

            Points = new List<Point>();

            AlgModeSelect.Items.AddRange(AlgModes);
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            //update pos
            cursor = this.PointToClient(Cursor.Position);
            MouseLocation.Text = "X: " + cursor.X + " Y: " + cursor.Y;
        }

        private void MouseLocation_Click(object sender, EventArgs e)
        {

        }

        private void UniformDistGen(int numOfPoints)
        {
            int x, y;
            for (int i = 0; i < numOfPoints; i++)
            {
                do
                {
                    x = rnd.Next(MinX, MaxX);
                    y = rnd.Next(MinY, MaxY);
                } while (Points.Find(point => (point.X == x && point.Y == y)) != default);

                Points.Add(new Point(x, y));
                g.DrawEllipse(penRed, x - (PointHeight / 2), y - (PointHeight / 2), PointWidth, PointHeight);
            }
        }

        private void GenerateBtn_Click(object sender, EventArgs e)
        {
            if (PointNum.Text == "")
                return;

            Clear();

            int numOfPoints = Convert.ToInt32(PointNum.Text);

            UniformDistGen(numOfPoints);
        }

        private void CalculateBtn_Click(object sender, EventArgs e)
        {
            if (AlgModeSelect.SelectedIndex == -1)
                return;

            if (!calculated)
                return;

            var edges = new List<Tuple<Point, Point>>();

            var watch = new System.Diagnostics.Stopwatch();

            watch.Start();
            if (AlgModeSelect.SelectedIndex == 0)
            {
                edges = GetMinimalWeightedTriangulation(Points);
            }
            else
            {
                edges = GetHamiltonTriangulation(Points);
            }
            watch.Stop();

            TimeLbl.Text = "Čas: " + watch.ElapsedMilliseconds + " ms";

            foreach (var edge in edges)
            {
                g.DrawLine(penBlue, edge.Item1, edge.Item2);
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

        public List<Tuple<Point, Point>> GetMinimalWeightedTriangulation(List<Point> points)
        {
            int n = points.Count;
            var edges = new List<Tuple<double, Point, Point>>();
            var acceptedEdges = new List<Tuple<Point, Point>>();

            // Izračun konveksne lupine in določanje vrednosti k
            var convexHull = JarvisMarch(points);
            int k = convexHull.Count;

            // Povežemo vse točke in uredimo seznam daljic glede na njihovo dolžino
            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    double distance = Math.Sqrt(Math.Pow(points[i].X - points[j].X, 2) +
                                                Math.Pow(points[i].Y - points[j].Y, 2));
                    edges.Add(new Tuple<double, Point, Point>(distance, points[i], points[j]));
                }
            }
            edges = edges.OrderBy(e => e.Item1).ToList();

            // Najkrajšo daljico vzamemo kot začetno daljico
            acceptedEdges.Add(new Tuple<Point, Point>(edges[0].Item2, edges[0].Item3));
            edges.RemoveAt(0);

            int targetEdges = 3 * n - 3 - k;

            // Preostale daljice obravnavamo po vrstnem redu
            foreach (var edge in edges)
            {
                if (acceptedEdges.Count >= targetEdges) break;

                bool intersects = false;

                foreach (var acceptedEdge in acceptedEdges)
                {
                    if (Intersect(edge.Item2, edge.Item3, acceptedEdge.Item1, acceptedEdge.Item2))
                    {
                        intersects = true;
                        break;
                    }
                }

                // Dodamo daljico v seznam sprejetih daljic, če ne seka nobene sprejete daljice
                if (!intersects)
                {
                    acceptedEdges.Add(new Tuple<Point, Point>(edge.Item2, edge.Item3));
                }
            }

            EdgesCount.Text = acceptedEdges.Count.ToString() + " " + (3 * n - 3 - k).ToString();

            return acceptedEdges;
        }

        private bool Intersect(Point p1, Point p2, Point p3, Point p4)
        {
            float D = (p2.X - p1.X) * (p4.Y - p3.Y) - (p4.X - p3.X) * (p2.Y - p1.Y);
            float A = (p4.X - p3.X) * (p1.Y - p3.Y) - (p1.X - p3.X) * (p4.Y - p3.Y);
            float B = (p2.X - p1.X) * (p1.Y - p3.Y) - (p1.X - p3.X) * (p2.Y - p1.Y);
            double Ua = A / D;
            double Ub = B / D;

            if (A == 0 && B == 0 && D == 0)
            {
                return true;
            }

            return 0 < Ua && Ua < 1 && 0 < Ub && Ub < 1;
        }

        private static int Orientation(Point p, Point q, Point r)
        {
            int val = (q.Y - p.Y) * (r.X - q.X) - (q.X - p.X) * (r.Y - q.Y);

            if (val == 0) return 0;
            return (val > 0) ? 1 : 2;
        }

        public static List<Point> JarvisMarch(List<Point> points)
        {
            if (points.Count < 3)
            {
                return new List<Point>(points);
            }

            List<Point> hull = new List<Point>();

            int leftMostIndex = 0;
            for (int i = 1; i < points.Count; i++)
            {
                if (points[i].X < points[leftMostIndex].X)
                {
                    leftMostIndex = i;
                }
            }

            int p = leftMostIndex;
            int q;

            do
            {
                hull.Add(points[p]);

                q = (p + 1) % points.Count;
                for (int i = 0; i < points.Count; i++)
                {
                    if (Orientation(points[p], points[i], points[q]) == 2)
                    {
                        q = i;
                    }
                }

                p = q;

            } while (p != leftMostIndex);

            return hull;
        }

        public List<Tuple<Point, Point>> GetHamiltonTriangulation(List<Point> points)
        {
            List<Tuple<Point, Point>> lines = new List<Tuple<Point, Point>>();
            List<List<Point>> hulls = new List<List<Point>>();
            // Izračunamo vse lupine
            while (points.Count > 0)
            {
                if (points.Count <= 3)
                {
                    hulls.Add(points);
                    break;
                }

                var hull = JarvisMarch(points);
                hulls.Add(hull);
                foreach (var point in hull)
                {
                    points.Remove(point);
                }
            }

            // Povežemo lupine tako, da dobimo spiralo
            List<Point> spiralPoints = new List<Point>();
            foreach (var hull in hulls)
            {
                Point hullFirst = new Point();
                Point hullLast = new Point();

                if (spiralPoints.Count != 0)
                    hullLast = spiralPoints.Last();
                
                spiralPoints.AddRange(hull);

                hullFirst = hull.First();

                // Če nismo na prvi lupini potem dodamo povezavo med prejsnjo in trenutno lupino
                if(!hullLast.IsEmpty)
                    lines.Add(new Tuple<Point, Point>(hullFirst, hullLast));

                // Povezemo ostale daljice konveksn lupine
                if (hull.Count > 1)
                {
                    for (int i = 1; i < hull.Count; i++)
                    {
                        lines.Add(new Tuple<Point, Point>(hull[i - 1], hull[i]));
                    }
                }
            }

            // Prvi trikotnik
            lines.Add(new Tuple<Point, Point>(hulls[0].First(), hulls[0].Last()));
            //lines.Add(new Tuple<Point, Point>(hulls[0].First(), hulls[1].First()));
            lines.Add(new Tuple<Point, Point>(hulls[1].First(), hulls[0].Last()));
            
            for (int j = 1; j < hulls.Count; j++)
            {
                for (int i = 0; i < hulls[j].Count; i++)
                {
                    bool intersects;
                    if (i <= hulls[j-1].Count - 1)
                    {
                        intersects = false;
                        foreach (var line in lines)
                        {
                            if (Intersect(hulls[j][i], hulls[j-1][i], line.Item1, line.Item2))
                            {
                                intersects = true;
                                break;
                            }
                        }

                        if (!intersects)
                        {
                            lines.Add(new Tuple<Point, Point>(hulls[j][i], hulls[j-1][i]));
                        }
                    }

                    if (i + 1 <= hulls[0].Count - 1)
                    {
                        intersects = false;
                        foreach (var line in lines)
                        {
                            if (Intersect(hulls[j][i], hulls[j-1][i + 1], line.Item1, line.Item2))
                            {
                                intersects = true;
                                break;
                            }
                        }

                        if (!intersects)
                        {
                            lines.Add(new Tuple<Point, Point>(hulls[j][i], hulls[j-1][i + 1]));
                        }
                    }
                }
            }
            
            return lines;
        }
    }
}
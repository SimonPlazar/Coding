using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Forms.Integration;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;


namespace UI___Nevronska_Mreza
{
    public partial class Form1 : Form
    {
        InkCanvas inkCanvas;
        DrawingAttributes inkDA;
        ElementHost host;

        private const int PointHeight = 5;
        private const int PointWidth = 5;
        private const int CanvasHeight = 419;
        private const int CanvasWidth = 700;

        Point cursor;

        int PointNum = 50;

        public Form1()
        {
            InitializeComponent();

            inkCanvas = new InkCanvas();

            inkDA = new DrawingAttributes();
            inkDA.Color = Colors.Red;
            inkDA.Height = PointHeight;
            inkDA.Width = PointWidth;

            inkCanvas.DefaultDrawingAttributes = inkDA;
            
            host = new ElementHost();
            host.Child = inkCanvas;
            Controls.Add(host);

            host.Width = 700;
            host.Height = 419;
        }

        //Update Pos
        private void Form1_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            //update pos
            cursor = this.PointToClient(System.Windows.Forms.Cursor.Position);
            MouseLocation.Text = "X: " + cursor.X + " Y: " + cursor.Y;
        }

        //Vectorise the sign
        private void TransformBtn_Click(object sender, EventArgs e)
        {
            //if no stroke drawn
            if (inkCanvas.Strokes.Count == 0) return;

            Stroke s = inkCanvas.Strokes[0];
            List<Point> list = new List<Point>();

            //convert stroke to point list
            foreach (StylusPoint sp in s.StylusPoints)
            {
                list.Add(new Point((int)sp.X, (int)sp.Y));
            }

            //Shorten the list and interpolate the points
            Point first = list.First();
            Point last = list.Last();

            list.RemoveAt(0);
            list.RemoveAt(list.Count - 1);
            while (list.Count > PointNum - 2) {
                for (int i = 1; i < list.Count - 1; i++)
                {
                    if (list.Count == PointNum - 2) break;
                    Point p1 = list[i - 1];
                    Point p2 = list[i];
                    Point middle = midpoint(p1, p2);

                    list.RemoveAt(i - 1);
                    list.RemoveAt(i);

                    list.Insert(i, middle);
                }
            }
            list.Insert(0, first);
            list.Add(last);

            //create new stroke from point list
            StylusPointCollection spc = new StylusPointCollection();
            CordBox.Text = list.Count + "\n";
            foreach (Point p in list)
            {
                spc.Add(new StylusPoint(p.X, p.Y));
                CordBox.Text += p.X + " " + p.Y + "\n";
            }

            inkCanvas.Strokes.Clear();
            inkCanvas.Strokes.Add(new Stroke(spc, inkDA));
        }

        //Find the middle point between two points
        private Point midpoint(Point a, Point b)
        {
            return new Point( (int)((a.X + b.X) / 2), (int)((a.Y + b.Y) / 2) );
        }

        //Clean InkCanvas
        private void ClearBtn_Click(object sender, EventArgs e)
        {
            inkCanvas.Strokes.Clear();
        }

        //Normalize the Points in the List and returns a List with float touple
        public List<(float, float)> NormalizeSignPointList(List<Point> list)
        {
            List<(float, float)> result = new List<(float, float)>();

            foreach(Point p in list)
            {
                result.Add( ((float)(p.X / CanvasWidth), (float)(p.Y / CanvasHeight)) );
            }

            return result;
        }
    }
}

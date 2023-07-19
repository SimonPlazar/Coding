namespace RGEO_vaja4
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            MouseLocation = new Label();
            GenerateBtn = new Button();
            CalculateBtn = new Button();
            PointNum = new TextBox();
            ClearBtn = new Button();
            EdgesCount = new Label();
            AlgModeSelect = new ComboBox();
            TimeLbl = new Label();
            SuspendLayout();
            // 
            // MouseLocation
            // 
            MouseLocation.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
            MouseLocation.AutoSize = true;
            MouseLocation.Location = new Point(12, 416);
            MouseLocation.Name = "MouseLocation";
            MouseLocation.Size = new Size(70, 25);
            MouseLocation.TabIndex = 0;
            MouseLocation.Text = "X: - Y: -";
            MouseLocation.Click += MouseLocation_Click;
            // 
            // GenerateBtn
            // 
            GenerateBtn.Location = new Point(612, 88);
            GenerateBtn.Name = "GenerateBtn";
            GenerateBtn.Size = new Size(176, 34);
            GenerateBtn.TabIndex = 1;
            GenerateBtn.Text = "Generate";
            GenerateBtn.UseVisualStyleBackColor = true;
            GenerateBtn.Click += GenerateBtn_Click;
            // 
            // CalculateBtn
            // 
            CalculateBtn.Location = new Point(612, 128);
            CalculateBtn.Name = "CalculateBtn";
            CalculateBtn.Size = new Size(176, 34);
            CalculateBtn.TabIndex = 2;
            CalculateBtn.Text = "Calculate";
            CalculateBtn.UseVisualStyleBackColor = true;
            CalculateBtn.Click += CalculateBtn_Click;
            // 
            // PointNum
            // 
            PointNum.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Right;
            PointNum.Location = new Point(612, 51);
            PointNum.Name = "PointNum";
            PointNum.Size = new Size(176, 31);
            PointNum.TabIndex = 9;
            // 
            // ClearBtn
            // 
            ClearBtn.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            ClearBtn.Location = new Point(612, 404);
            ClearBtn.Name = "ClearBtn";
            ClearBtn.Size = new Size(176, 34);
            ClearBtn.TabIndex = 13;
            ClearBtn.Text = "Clear";
            ClearBtn.UseVisualStyleBackColor = true;
            ClearBtn.Click += ClearBtn_Click;
            // 
            // EdgesCount
            // 
            EdgesCount.AutoSize = true;
            EdgesCount.Location = new Point(157, 416);
            EdgesCount.Name = "EdgesCount";
            EdgesCount.Size = new Size(17, 25);
            EdgesCount.TabIndex = 14;
            EdgesCount.Text = " ";
            // 
            // AlgModeSelect
            // 
            AlgModeSelect.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Right;
            AlgModeSelect.FormattingEnabled = true;
            AlgModeSelect.Location = new Point(612, 12);
            AlgModeSelect.Name = "AlgModeSelect";
            AlgModeSelect.RightToLeft = RightToLeft.Yes;
            AlgModeSelect.Size = new Size(176, 33);
            AlgModeSelect.TabIndex = 15;
            AlgModeSelect.Text = "Select Alg. Mode";
            // 
            // TimeLbl
            // 
            TimeLbl.AutoSize = true;
            TimeLbl.Location = new Point(612, 165);
            TimeLbl.Name = "TimeLbl";
            TimeLbl.Size = new Size(56, 25);
            TimeLbl.TabIndex = 16;
            TimeLbl.Text = "Čas: -";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(TimeLbl);
            Controls.Add(AlgModeSelect);
            Controls.Add(EdgesCount);
            Controls.Add(ClearBtn);
            Controls.Add(PointNum);
            Controls.Add(CalculateBtn);
            Controls.Add(GenerateBtn);
            Controls.Add(MouseLocation);
            Name = "Form1";
            Text = "Form1";
            MouseMove += Form1_MouseMove;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label MouseLocation;
        private Button GenerateBtn;
        private Button CalculateBtn;
        private TextBox PointNum;
        private Button ClearBtn;
        private Label EdgesCount;
        private ComboBox AlgModeSelect;
        private Label TimeLbl;
    }
}
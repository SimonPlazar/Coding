namespace RGEO_vaja2
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
            DistModeSelect = new ComboBox();
            AlgModeSelect = new ComboBox();
            PointNum = new TextBox();
            GenerateBtn = new Button();
            CalculateBtn = new Button();
            MouseLocation = new Label();
            ClearBtn = new Button();
            TimeLabel = new Label();
            SuspendLayout();
            // 
            // DistModeSelect
            // 
            DistModeSelect.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Right;
            DistModeSelect.FormattingEnabled = true;
            DistModeSelect.Location = new Point(712, 12);
            DistModeSelect.Name = "DistModeSelect";
            DistModeSelect.RightToLeft = RightToLeft.Yes;
            DistModeSelect.Size = new Size(176, 33);
            DistModeSelect.TabIndex = 5;
            DistModeSelect.Text = "Select Dist. Mode";
            // 
            // AlgModeSelect
            // 
            AlgModeSelect.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Right;
            AlgModeSelect.FormattingEnabled = true;
            AlgModeSelect.Location = new Point(712, 51);
            AlgModeSelect.Name = "AlgModeSelect";
            AlgModeSelect.RightToLeft = RightToLeft.Yes;
            AlgModeSelect.Size = new Size(176, 33);
            AlgModeSelect.TabIndex = 6;
            AlgModeSelect.Text = "Select Alg. Mode";
            // 
            // PointNum
            // 
            PointNum.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Right;
            PointNum.Location = new Point(712, 90);
            PointNum.Name = "PointNum";
            PointNum.Size = new Size(176, 31);
            PointNum.TabIndex = 8;
            // 
            // GenerateBtn
            // 
            GenerateBtn.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Right;
            GenerateBtn.Location = new Point(712, 127);
            GenerateBtn.Name = "GenerateBtn";
            GenerateBtn.Size = new Size(176, 34);
            GenerateBtn.TabIndex = 9;
            GenerateBtn.Text = "Generate";
            GenerateBtn.UseVisualStyleBackColor = true;
            GenerateBtn.Click += GenerateBtn_Click;
            // 
            // CalculateBtn
            // 
            CalculateBtn.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            CalculateBtn.Location = new Point(712, 167);
            CalculateBtn.Name = "CalculateBtn";
            CalculateBtn.Size = new Size(176, 34);
            CalculateBtn.TabIndex = 10;
            CalculateBtn.Text = "Calculate Hull";
            CalculateBtn.UseVisualStyleBackColor = true;
            CalculateBtn.Click += CalculateBtn_Click;
            // 
            // MouseLocation
            // 
            MouseLocation.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
            MouseLocation.AutoSize = true;
            MouseLocation.Location = new Point(12, 616);
            MouseLocation.Name = "MouseLocation";
            MouseLocation.Size = new Size(70, 25);
            MouseLocation.TabIndex = 11;
            MouseLocation.Text = "X: - Y: -";
            MouseLocation.TextAlign = ContentAlignment.TopCenter;
            // 
            // ClearBtn
            // 
            ClearBtn.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            ClearBtn.Location = new Point(712, 604);
            ClearBtn.Name = "ClearBtn";
            ClearBtn.Size = new Size(176, 34);
            ClearBtn.TabIndex = 12;
            ClearBtn.Text = "Clear";
            ClearBtn.UseVisualStyleBackColor = true;
            ClearBtn.Click += ClearBtn_Click;
            // 
            // TimeLabel
            // 
            TimeLabel.AutoSize = true;
            TimeLabel.Location = new Point(712, 204);
            TimeLabel.Name = "TimeLabel";
            TimeLabel.Size = new Size(0, 25);
            TimeLabel.TabIndex = 13;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(900, 650);
            Controls.Add(TimeLabel);
            Controls.Add(ClearBtn);
            Controls.Add(MouseLocation);
            Controls.Add(CalculateBtn);
            Controls.Add(GenerateBtn);
            Controls.Add(PointNum);
            Controls.Add(AlgModeSelect);
            Controls.Add(DistModeSelect);
            Name = "Form1";
            Text = "Form1";
            MouseMove += Form1_MouseMove;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ComboBox DistModeSelect;
        private ComboBox AlgModeSelect;
        private TextBox PointNum;
        private Button GenerateBtn;
        private Button button1;
        private Label MouseLocation;
        private Button ClearBtn;
        private Button CalculateBtn;
        private Label TimeLabel;
    }
}
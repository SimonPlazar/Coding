namespace RGEO_vaja1
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
            CordList = new RichTextBox();
            Clear = new Button();
            ModeSelect = new ComboBox();
            Calculate = new Button();
            CreatePointBtn = new Button();
            cordX = new TextBox();
            cordY = new TextBox();
            CheckBox = new CheckBox();
            SuspendLayout();
            // 
            // MouseLocation
            // 
            MouseLocation.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
            MouseLocation.AutoSize = true;
            MouseLocation.Location = new Point(12, 510);
            MouseLocation.Name = "MouseLocation";
            MouseLocation.Size = new Size(70, 25);
            MouseLocation.TabIndex = 0;
            MouseLocation.Text = "X: - Y: -";
            MouseLocation.TextAlign = ContentAlignment.TopCenter;
            // 
            // CordList
            // 
            CordList.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Right;
            CordList.Location = new Point(773, 12);
            CordList.Name = "CordList";
            CordList.Size = new Size(193, 526);
            CordList.TabIndex = 2;
            CordList.Text = "";
            // 
            // Clear
            // 
            Clear.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            Clear.Location = new Point(655, 504);
            Clear.Name = "Clear";
            Clear.Size = new Size(112, 34);
            Clear.TabIndex = 3;
            Clear.Text = "Clear";
            Clear.UseVisualStyleBackColor = true;
            Clear.Click += Clear_Click;
            // 
            // ModeSelect
            // 
            ModeSelect.FormattingEnabled = true;
            ModeSelect.Location = new Point(622, 12);
            ModeSelect.Name = "ModeSelect";
            ModeSelect.RightToLeft = RightToLeft.Yes;
            ModeSelect.Size = new Size(145, 33);
            ModeSelect.TabIndex = 4;
            ModeSelect.Text = "Select Mode";
            // 
            // Calculate
            // 
            Calculate.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            Calculate.Location = new Point(537, 504);
            Calculate.Name = "Calculate";
            Calculate.Size = new Size(112, 34);
            Calculate.TabIndex = 5;
            Calculate.Text = "Calculate";
            Calculate.UseVisualStyleBackColor = true;
            Calculate.Click += Calculate_Click;
            // 
            // CreatePointBtn
            // 
            CreatePointBtn.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
            CreatePointBtn.Location = new Point(317, 505);
            CreatePointBtn.Name = "CreatePointBtn";
            CreatePointBtn.Size = new Size(112, 34);
            CreatePointBtn.TabIndex = 6;
            CreatePointBtn.Text = "Set";
            CreatePointBtn.UseVisualStyleBackColor = true;
            CreatePointBtn.MouseClick += CreatePointBtn_MouseClick;
            // 
            // cordX
            // 
            cordX.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            cordX.Location = new Point(155, 508);
            cordX.Name = "cordX";
            cordX.Size = new Size(75, 31);
            cordX.TabIndex = 7;
            // 
            // cordY
            // 
            cordY.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            cordY.Location = new Point(236, 508);
            cordY.Name = "cordY";
            cordY.Size = new Size(75, 31);
            cordY.TabIndex = 8;
            // 
            // CheckBox
            // 
            CheckBox.AutoSize = true;
            CheckBox.Location = new Point(435, 508);
            CheckBox.Name = "CheckBox";
            CheckBox.Size = new Size(69, 29);
            CheckBox.TabIndex = 9;
            CheckBox.Text = "Line";
            CheckBox.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(978, 544);
            Controls.Add(CheckBox);
            Controls.Add(cordY);
            Controls.Add(cordX);
            Controls.Add(CreatePointBtn);
            Controls.Add(Calculate);
            Controls.Add(ModeSelect);
            Controls.Add(Clear);
            Controls.Add(CordList);
            Controls.Add(MouseLocation);
            Name = "Form1";
            Text = "Uvod v Računalniško Geometrijo";
            MouseClick += Form1_MouseClick;
            MouseMove += Form1_MouseMove;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label MouseLocation;
        private RichTextBox CordList;
        private Button Clear;
        private ComboBox ModeSelect;
        private Button Calculate;
        private Button CreatePointBtn;
        private TextBox cordX;
        private TextBox cordY;
        private CheckBox CheckBox;
    }
}
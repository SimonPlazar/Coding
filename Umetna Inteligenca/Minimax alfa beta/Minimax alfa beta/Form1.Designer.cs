namespace Minimax_alfa_beta
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
            DepthSelect = new ComboBox();
            MouseLocation = new Label();
            Winner = new Label();
            ClearBtn = new Button();
            SuspendLayout();
            // 
            // DepthSelect
            // 
            DepthSelect.FormattingEnabled = true;
            DepthSelect.Location = new Point(12, 12);
            DepthSelect.Name = "DepthSelect";
            DepthSelect.RightToLeft = RightToLeft.Yes;
            DepthSelect.Size = new Size(145, 33);
            DepthSelect.TabIndex = 5;
            DepthSelect.Text = "Select Depth";
            DepthSelect.SelectedIndexChanged += DepthSelect_SelectedIndexChanged;
            // 
            // MouseLocation
            // 
            MouseLocation.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
            MouseLocation.AutoSize = true;
            MouseLocation.Location = new Point(12, 416);
            MouseLocation.Name = "MouseLocation";
            MouseLocation.Size = new Size(70, 25);
            MouseLocation.TabIndex = 6;
            MouseLocation.Text = "X: - Y: -";
            MouseLocation.TextAlign = ContentAlignment.TopCenter;
            // 
            // Winner
            // 
            Winner.AutoSize = true;
            Winner.Location = new Point(12, 391);
            Winner.Name = "Winner";
            Winner.Size = new Size(84, 25);
            Winner.TabIndex = 7;
            Winner.Text = "Winner: -";
            // 
            // ClearBtn
            // 
            ClearBtn.Location = new Point(12, 354);
            ClearBtn.Name = "ClearBtn";
            ClearBtn.Size = new Size(112, 34);
            ClearBtn.TabIndex = 8;
            ClearBtn.Text = "Reset";
            ClearBtn.UseVisualStyleBackColor = true;
            ClearBtn.Click += ClearBtn_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(ClearBtn);
            Controls.Add(Winner);
            Controls.Add(MouseLocation);
            Controls.Add(DepthSelect);
            Name = "Form1";
            Text = "Form1";
            Paint += Form1_Paint;
            MouseClick += Form1_MouseClick;
            MouseMove += Form1_MouseMove;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ComboBox DepthSelect;
        private Label MouseLocation;
        private Label Winner;
        private Button ClearBtn;
    }
}
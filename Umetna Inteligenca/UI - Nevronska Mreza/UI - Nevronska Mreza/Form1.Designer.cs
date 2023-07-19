namespace UI___Nevronska_Mreza
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.MouseLocation = new System.Windows.Forms.Label();
            this.TransformBtn = new System.Windows.Forms.Button();
            this.CordBox = new System.Windows.Forms.RichTextBox();
            this.ClearBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // MouseLocation
            // 
            this.MouseLocation.AutoSize = true;
            this.MouseLocation.Location = new System.Drawing.Point(12, 428);
            this.MouseLocation.Name = "MouseLocation";
            this.MouseLocation.Size = new System.Drawing.Size(42, 13);
            this.MouseLocation.TabIndex = 0;
            this.MouseLocation.Text = "X: - Y: -";
            // 
            // TransformBtn
            // 
            this.TransformBtn.Location = new System.Drawing.Point(713, 12);
            this.TransformBtn.Name = "TransformBtn";
            this.TransformBtn.Size = new System.Drawing.Size(75, 23);
            this.TransformBtn.TabIndex = 1;
            this.TransformBtn.Text = "Transform";
            this.TransformBtn.UseVisualStyleBackColor = true;
            this.TransformBtn.Click += new System.EventHandler(this.TransformBtn_Click);
            // 
            // CordBox
            // 
            this.CordBox.Location = new System.Drawing.Point(713, 41);
            this.CordBox.Name = "CordBox";
            this.CordBox.Size = new System.Drawing.Size(75, 405);
            this.CordBox.TabIndex = 2;
            this.CordBox.Text = "";
            // 
            // ClearBtn
            // 
            this.ClearBtn.Location = new System.Drawing.Point(632, 423);
            this.ClearBtn.Name = "ClearBtn";
            this.ClearBtn.Size = new System.Drawing.Size(75, 23);
            this.ClearBtn.TabIndex = 3;
            this.ClearBtn.Text = "Clear";
            this.ClearBtn.UseVisualStyleBackColor = true;
            this.ClearBtn.Click += new System.EventHandler(this.ClearBtn_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.ClearBtn);
            this.Controls.Add(this.CordBox);
            this.Controls.Add(this.TransformBtn);
            this.Controls.Add(this.MouseLocation);
            this.Name = "Form1";
            this.Text = "Form1";
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseMove);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label MouseLocation;
        private System.Windows.Forms.Button TransformBtn;
        private System.Windows.Forms.RichTextBox CordBox;
        private System.Windows.Forms.Button ClearBtn;
    }
}


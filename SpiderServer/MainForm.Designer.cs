namespace SpiderServer
{
	partial class MainForm
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			BtnFront = new Button();
			BtnBack = new Button();
			BntLeft = new Button();
			BtnRight = new Button();
			richTextBox1 = new RichTextBox();
			label1 = new Label();
			SuspendLayout();
			// 
			// BtnFront
			// 
			BtnFront.AccessibleName = "";
			BtnFront.Location = new Point(94, 21);
			BtnFront.Name = "BtnFront";
			BtnFront.Size = new Size(75, 23);
			BtnFront.TabIndex = 0;
			BtnFront.Text = "Inainte";
			BtnFront.UseVisualStyleBackColor = true;
			BtnFront.Click += BtnFront_Click;
			// 
			// BtnBack
			// 
			BtnBack.AccessibleName = "BtnBack";
			BtnBack.Location = new Point(94, 79);
			BtnBack.Name = "BtnBack";
			BtnBack.Size = new Size(75, 23);
			BtnBack.TabIndex = 1;
			BtnBack.Text = "In spate";
			BtnBack.UseVisualStyleBackColor = true;
			BtnBack.Click += BtnBack_Click;
			// 
			// BntLeft
			// 
			BntLeft.AccessibleName = "BntLeft";
			BntLeft.Location = new Point(23, 50);
			BntLeft.Name = "BntLeft";
			BntLeft.Size = new Size(75, 23);
			BntLeft.TabIndex = 2;
			BntLeft.Text = "In stanga";
			BntLeft.UseVisualStyleBackColor = true;
			BntLeft.Click += BntLeft_Click;
			// 
			// BtnRight
			// 
			BtnRight.AccessibleName = "";
			BtnRight.Location = new Point(165, 50);
			BtnRight.Name = "BtnRight";
			BtnRight.Size = new Size(75, 23);
			BtnRight.TabIndex = 3;
			BtnRight.Text = "In dreapta";
			BtnRight.UseVisualStyleBackColor = true;
			BtnRight.Click += BtnRight_Click;
			// 
			// richTextBox1
			// 
			richTextBox1.AccessibleName = "LogsOutput";
			richTextBox1.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			richTextBox1.Location = new Point(12, 120);
			richTextBox1.Name = "richTextBox1";
			richTextBox1.Size = new Size(360, 239);
			richTextBox1.TabIndex = 4;
			richTextBox1.Text = "[*] Comanda executata cu succes";
			// 
			// label1
			// 
			label1.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			label1.AutoSize = true;
			label1.Location = new Point(293, 9);
			label1.Name = "label1";
			label1.Size = new Size(79, 15);
			label1.TabIndex = 5;
			label1.Text = "Statut: Online";
			// 
			// MainForm
			// 
			AutoScaleDimensions = new SizeF(7F, 15F);
			AutoScaleMode = AutoScaleMode.Font;
			BackColor = Color.White;
			ClientSize = new Size(384, 371);
			Controls.Add(label1);
			Controls.Add(richTextBox1);
			Controls.Add(BtnRight);
			Controls.Add(BntLeft);
			Controls.Add(BtnBack);
			Controls.Add(BtnFront);
			Icon = (Icon)resources.GetObject("$this.Icon");
			MinimumSize = new Size(400, 410);
			Name = "MainForm";
			Text = "Spider controller";
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private Button BtnFront;
		private Button BtnBack;
		private Button BntLeft;
		private Button BtnRight;
		private RichTextBox richTextBox1;
		private Label label1;
	}
}
/*
 * Created by SharpDevelop.
 * User: Sebastien
 * Date: 20/08/2013
 * Time: 18:44
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace ArduinoTrayIcon
{
	partial class FormPort
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			this.comboBox1 = new System.Windows.Forms.ComboBox();
			this.buttonOk = new System.Windows.Forms.Button();
			this.buttonAnnuler = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// comboBox1
			// 
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Location = new System.Drawing.Point(84, 15);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new System.Drawing.Size(86, 21);
			this.comboBox1.TabIndex = 0;
			// 
			// buttonOk
			// 
			this.buttonOk.Location = new System.Drawing.Point(28, 42);
			this.buttonOk.Name = "buttonOk";
			this.buttonOk.Size = new System.Drawing.Size(74, 23);
			this.buttonOk.TabIndex = 1;
			this.buttonOk.Text = "OK";
			this.buttonOk.UseVisualStyleBackColor = true;
			this.buttonOk.Click += new System.EventHandler(this.ButtonOkClick);
			// 
			// buttonAnnuler
			// 
			this.buttonAnnuler.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonAnnuler.Location = new System.Drawing.Point(108, 42);
			this.buttonAnnuler.Name = "buttonAnnuler";
			this.buttonAnnuler.Size = new System.Drawing.Size(75, 23);
			this.buttonAnnuler.TabIndex = 2;
			this.buttonAnnuler.Text = "Annuler";
			this.buttonAnnuler.UseVisualStyleBackColor = true;
			this.buttonAnnuler.Click += new System.EventHandler(this.ButtonAnnulerClick);
			// 
			// label1
			// 
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(37, 16);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(41, 21);
			this.label1.TabIndex = 3;
			this.label1.Text = "Port :";
			// 
			// FormPort
			// 
			this.AcceptButton = this.buttonOk;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.buttonAnnuler;
			this.ClientSize = new System.Drawing.Size(209, 82);
			this.ControlBox = false;
			this.Controls.Add(this.label1);
			this.Controls.Add(this.buttonAnnuler);
			this.Controls.Add(this.buttonOk);
			this.Controls.Add(this.comboBox1);
			this.Name = "FormPort";
			this.Text = "Choix du port";
			this.Load += new System.EventHandler(this.FormPortLoad);
			this.ResumeLayout(false);
		}
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button buttonAnnuler;
		private System.Windows.Forms.Button buttonOk;
		private System.Windows.Forms.ComboBox comboBox1;
	}
}

/*
 * Created by SharpDevelop.
 * User: Sebastien
 * Date: 20/08/2013
 * Time: 21:39
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace ArduinoTrayIcon
{
	partial class FormTime
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
			this.dateTimePicker = new System.Windows.Forms.DateTimePicker();
			this.buttonAnnuler = new System.Windows.Forms.Button();
			this.buttonOk = new System.Windows.Forms.Button();
			this.buttonNow = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// dateTimePicker
			// 
			this.dateTimePicker.CustomFormat = "le dddd d MMMM yyyy  à  HH:mm:ss";
			this.dateTimePicker.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
			this.dateTimePicker.Location = new System.Drawing.Point(12, 12);
			this.dateTimePicker.Name = "dateTimePicker";
			this.dateTimePicker.ShowUpDown = true;
			this.dateTimePicker.Size = new System.Drawing.Size(239, 20);
			this.dateTimePicker.TabIndex = 0;
			// 
			// buttonAnnuler
			// 
			this.buttonAnnuler.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonAnnuler.Location = new System.Drawing.Point(133, 74);
			this.buttonAnnuler.Name = "buttonAnnuler";
			this.buttonAnnuler.Size = new System.Drawing.Size(75, 23);
			this.buttonAnnuler.TabIndex = 4;
			this.buttonAnnuler.Text = "Annuler";
			this.buttonAnnuler.UseVisualStyleBackColor = true;
			this.buttonAnnuler.Click += new System.EventHandler(this.ButtonAnnulerClick);
			// 
			// buttonOk
			// 
			this.buttonOk.Location = new System.Drawing.Point(53, 74);
			this.buttonOk.Name = "buttonOk";
			this.buttonOk.Size = new System.Drawing.Size(74, 23);
			this.buttonOk.TabIndex = 3;
			this.buttonOk.Text = "OK";
			this.buttonOk.UseVisualStyleBackColor = true;
			this.buttonOk.Click += new System.EventHandler(this.ButtonOkClick);
			// 
			// buttonNow
			// 
			this.buttonNow.Location = new System.Drawing.Point(95, 42);
			this.buttonNow.Name = "buttonNow";
			this.buttonNow.Size = new System.Drawing.Size(74, 23);
			this.buttonNow.TabIndex = 5;
			this.buttonNow.Text = "Maintenant";
			this.buttonNow.UseVisualStyleBackColor = true;
			this.buttonNow.Click += new System.EventHandler(this.ButtonNowClick);
			// 
			// FormTime
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(265, 120);
			this.ControlBox = false;
			this.Controls.Add(this.buttonNow);
			this.Controls.Add(this.buttonAnnuler);
			this.Controls.Add(this.buttonOk);
			this.Controls.Add(this.dateTimePicker);
			this.Name = "FormTime";
			this.Text = "Changer l\'heure";
			this.Load += new System.EventHandler(this.FormTimeLoad);
			this.ResumeLayout(false);
		}
		private System.Windows.Forms.Button buttonNow;
		private System.Windows.Forms.Button buttonOk;
		private System.Windows.Forms.Button buttonAnnuler;
		private System.Windows.Forms.DateTimePicker dateTimePicker;
	}
}

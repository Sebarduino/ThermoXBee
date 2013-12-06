/*
 * Created by SharpDevelop.
 * User: Sebastien
 * Date: 20/08/2013
 * Time: 18:44
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO.Ports;
using System.Configuration;

namespace ArduinoTrayIcon
{
	/// <summary>
	/// Description of Form1.
	/// </summary>
	public partial class FormPort : Form
	{
		public FormPort()
		{
			InitializeComponent();
		}
		
		void ButtonAnnulerClick(object sender, EventArgs e)
		{
			this.Close();
		}
		
		void ButtonOkClick(object sender, EventArgs e)
		{
			Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
			config.AppSettings.Settings.Clear();
			config.AppSettings.Settings.Add("port", comboBox1.SelectedItem.ToString());
			config.Save(ConfigurationSaveMode.Modified);
			this.Close();
		}
		
		void FormPortLoad(object sender, EventArgs e)
		{
			comboBox1.Items.AddRange(SerialPort.GetPortNames());
			Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
			comboBox1.SelectedItem = config.AppSettings.Settings["port"].Value;
		}
	}
}

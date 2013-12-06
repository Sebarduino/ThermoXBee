/*
 * Created by SharpDevelop.
 * User: Sebastien
 * Date: 20/08/2013
 * Time: 21:39
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Drawing;
using System.Windows.Forms;
using System.Configuration;
using System.IO.Ports;
using System.Text.RegularExpressions;

namespace ArduinoTrayIcon
{
	/// <summary>
	/// Description of FormTime.
	/// </summary>
	public partial class FormTime : Form
	{
		SerialPort serialPort;
		
		public FormTime()
		{
			InitializeComponent();
			
			//
			// TODO: Add constructor code after the InitializeComponent() call.
			//
		}
		
		
		void ButtonAnnulerClick(object sender, EventArgs e)
		{
			this.Close();
		}
		
		void ButtonOkClick(object sender, EventArgs e)
		{
			DateTime t = dateTimePicker.Value;
			string sTime = String.Format("setTime {0} {1}/{2}/{3} {4}:{5}:{6}",(((int)t.DayOfWeek)+6)%7,t.Day,t.Month,t.Year,t.Hour,t.Minute,t.Second);
			
			Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
			string port = config.AppSettings.Settings["port"].Value;
			serialPort = new SerialPort(port,9600);
			serialPort.ReadTimeout = 500;
    		serialPort.WriteTimeout = 500;
			serialPort.Open();
			serialPort.Write(sTime);
			serialPort.Close();
			this.Close();
		}
		
		void FormTimeLoad(object sender, EventArgs e)
		{
			Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
			string port = config.AppSettings.Settings["port"].Value;
			serialPort = new SerialPort(port,9600);
			serialPort.ReadTimeout = 500;
    		serialPort.WriteTimeout = 500;
			serialPort.Open();
			serialPort.Write("getTime");
			string time = serialPort.ReadLine();
			serialPort.Close();
			
			Regex myRegex=new Regex(@"(\d+)/(\d+)/(\d+) (\d+):(\d+):(\d+)");
			Match m= myRegex.Match(time);
			if(m.Success) {
				DateTime newTime = new DateTime(	Int32.Parse(m.Groups[3].Value),
				                                	Int32.Parse(m.Groups[2].Value),
				                                	Int32.Parse(m.Groups[1].Value),
				                                	Int32.Parse(m.Groups[4].Value),
				                                	Int32.Parse(m.Groups[5].Value),
				                                	Int32.Parse(m.Groups[6].Value));
				dateTimePicker.Value = newTime;
			}
			
			
			
		}
		
		void ButtonNowClick(object sender, EventArgs e)
		{
			dateTimePicker.Value = DateTime.Now;
		}
	}
}

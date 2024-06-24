using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace TaskManager
{
	public partial class RunWindow : Form
	{
		public ComboBox ComboBoxFileName
		{

			get
			{ 
			  return comboBoxFilename;
			}
		}
		public RunWindow()
		{
			InitializeComponent();
			Load();

		}

		public void Load()
		{
			StreamReader sr = new StreamReader("ProgramList.txt");
			while(!sr.EndOfStream)
			{
				string item = sr.ReadLine();
				comboBoxFilename.Items.Add(item);

			}

			sr.Close();
		}

		private void buttonOk_Click(object sender, EventArgs e)
		{
			try
			{
				string text = comboBoxFilename.Text;
				System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo(comboBoxFilename.Text);
				System.Diagnostics.Process process = new System.Diagnostics.Process();
				process.StartInfo = startInfo;
				process.Start();
				//if(!comboBoxFilename.Items.Contains(comboBoxFilename.Text))
				//	comboBoxFilename.Items.Insert(0,comboBoxFilename.Text);
				comboBoxFilename.Items.Remove(text);
				comboBoxFilename.Text = (text);
				comboBoxFilename.Items.Insert(0, text);
				this.Close();
			}
			catch(Exception ex) 
			{
				MessageBox.Show(this, ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				
			}

			


		}

		private void comboBoxFilename_KeyPress(object sender, KeyPressEventArgs e)
		{
			if (e.KeyChar == (char)Keys.Enter)
			{
				buttonOk_Click(sender, e);

			}

			
			
		}

		private void RunWindow_FormClosing(object sender, FormClosingEventArgs e)
		{
			comboBoxFilename.Focus();

		}
	}
}

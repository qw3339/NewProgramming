using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TaskManager
{
	public partial class RunWindow : Form
	{
		public RunWindow()
		{
			InitializeComponent();
		}

		private void buttonOk_Click(object sender, EventArgs e)
		{
			System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo(comboBoxFilename.Text);
			System.Diagnostics.Process process = new System.Diagnostics.Process();
			process.StartInfo = startInfo;
			process.Start();
			this.Close();


		}
	}
}

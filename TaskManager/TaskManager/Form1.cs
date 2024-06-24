using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Collections;


namespace TaskManager
{
    public partial class MainForm : Form
    {
        Dictionary<int, Process> d_processes;

		public MainForm()
        {
            InitializeComponent();
			SetColumns();
            statusStrip1.Items.Add("");
            LoadProcesses();
     
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			//LoadProcesses();		
			AddNewProcesses();
			
			RemoveOldProcesses();      
			statusStrip1.Items[0].Text = ($"Количество процессов: {listViewProcesses.Items.Count}");
			
		}

        void SetColumns()
        {
            listViewProcesses.Columns.Add("PID");
            listViewProcesses.Columns.Add("Name");
		}

        void LoadProcesses()
        {
            //listViewProcesses.Items.Clear();
            //Process[] processes = Process.GetProcesses();
            //for (int i = 0; i < processes.Length; i++)
            //{
            //    ListViewItem item = new ListViewItem();
            //    item.Text = processes[i].Id.ToString();
            //    item.SubItems.Add(processes[i].ProcessName);
            //    listViewProcesses.Items.Add(item);
            //}

            d_processes = Process.GetProcesses().ToDictionary(item => item.Id, item => item);
			foreach (KeyValuePair<int, Process> i in d_processes)
			{
                ListViewItem item = new ListViewItem();
                item.Text = i.Key.ToString();
                item.SubItems.Add(i.Value.ProcessName);
                listViewProcesses.Items.Add(item);				
			}
			//statusStrip1.Items[0].Text = ($"Количество процессов: {listViewProcesses.Items.Count}");      
        }

        void AddNewProcesses()
        {
			Dictionary<int, Process> d_processes = Process.GetProcesses().ToDictionary(item => item.Id, item => item);
            foreach (KeyValuePair<int, Process> i in d_processes)
			{
                if(!this.d_processes.ContainsKey(i.Key))
                {
					//this.d_processes.Add(i.Key, i.Value);
                    AddProcessesToListView(i.Value);
				}                  
            }
			//statusStrip1.Items[0].Text = ($"Количество процессов: {listViewProcesses.Items.Count}");
		}

        void RemoveOldProcesses()
        {

			this.d_processes = Process.GetProcesses().ToDictionary(item => item.Id, item => item);
			for (int i = 0; i < listViewProcesses.Items.Count; i++)
            {
                //string item_name = listViewProcesses.Items[i].Name;
                if (!d_processes.ContainsKey(Convert.ToInt32(listViewProcesses.Items[i].Text)))                
                    listViewProcesses.Items.RemoveAt(i);

                
            }
        }

		void AddProcessesToListView(Process process)
        {
            ListViewItem item = new ListViewItem();
            item.Text = process.Id.ToString();
            item.SubItems.Add(process.ProcessName);
            listViewProcesses.Items.Add(item);
		}

        void RemoveProcessesFromListView(int pid)
        {
            listViewProcesses.Items.RemoveByKey(pid.ToString());
        }


	}
}

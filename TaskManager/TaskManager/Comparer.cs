using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TaskManager
{
	class Comparer : IComparer //реализуем интерфэйс IComparer
	{
		int column;
		public Comparer(int column=0)
		{
			this.column = column;


		}

		public int Compare(object x, object y)
		{
			return String.Compare(((ListViewItem)x).SubItems[column].Text, ((ListViewItem)y).SubItems[column].Text);


		}



	}
}

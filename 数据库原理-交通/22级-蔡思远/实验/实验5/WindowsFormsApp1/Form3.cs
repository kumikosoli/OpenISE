using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }
        public Form3(string sid, string sname, string email, string grade)
        {
            InitializeComponent();
            textBox1.Text = sid;
            textBox2.Text = sname;
            textBox3.Text = email;
            textBox4.Text = grade;
        }

        private void button_qd3_Click(object sender, EventArgs e)
        {
            string sid = textBox1.Text.Trim();
            string sname = textBox2.Text.Trim();
            string email = textBox3.Text.Trim();
            string grade = textBox4.Text.Trim();
            string sql = "update STUDENTS set sname='" + sname + "',email='" + email + "',grade='" + grade + "' where sid='" + sid + "'";
            Form1.ExecuteSql(sql);
            this.Close();
        }
    }
}

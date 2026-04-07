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
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void button_qd_Click(object sender, EventArgs e)
        {
            string sid = textBox1.Text.Trim();
            string sname = textBox2.Text.Trim();
            string email = textBox3.Text.Trim();
            string grade = textBox4.Text.Trim();
            string sql = "insert into STUDENTS values('" + sid + "','" + sname + "','" + email + "','" + grade + "')";
            Form1.ExecuteSql(sql);
            this.Close();
        }
    }
}

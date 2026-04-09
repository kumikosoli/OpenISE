using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        static string connectionString = System.Configuration.ConfigurationManager.AppSettings["connectionString"];

        public Form1()
        {
            InitializeComponent();
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void grx2_Enter(object sender, EventArgs e)
        {

        }



        public static DataSet Query(String sql)
        {
            SqlConnection con = new SqlConnection(connectionString);
            SqlDataAdapter sda = new SqlDataAdapter(sql, con);
            DataSet ds = new DataSet();
            try
            {
                con.Open();
                sda.Fill(ds, "students");
                return ds;
            }
            catch (SqlException e)
            {
                throw new Exception(e.Message);
            }
            finally
            {
                sda.Dispose();
                con.Close();
            }
        }

        public static int ExecuteSql(String sql)
        {
            SqlConnection con = new SqlConnection(connectionString);
            SqlCommand cmd = new SqlCommand(sql, con);
            try
            {
                con.Open();
                int rows = cmd.ExecuteNonQuery();
                return rows;
            }
            catch (SqlException e)
            {
                throw new Exception(e.Message);
            }
            finally
            {
                cmd.Dispose();
                con.Close();
            }
        }

        private void text1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button11_Click(object sender, EventArgs e)
        {
            string sid = textBox1.Text.Trim();
            string sname = textBox2.Text.Trim();
            this.studentList.DataSource = Query("select * from students where sid like '%" + sid + "%' and sname like '%" + sname + "%'").Tables["students"];
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form2 childrenForm = new Form2();
            childrenForm.Owner = this;
            childrenForm.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {

            Form3 childrenForm = new Form3();
            childrenForm.Owner = this;
            childrenForm.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            int a = studentList.CurrentRow.Index;
            string sid = studentList.Rows[a].Cells[0].Value.ToString().Trim();
            string sql = "delete from STUDENTS where sid='" + sid + "'";

            if (ExecuteSql(sql) > 0)
            {
                MessageBox.Show("删除成功");
            }
        }
    }

    
}





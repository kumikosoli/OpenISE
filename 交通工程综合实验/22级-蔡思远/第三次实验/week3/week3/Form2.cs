using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Emgu.CV;
using System.Threading;

namespace week3
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private VideoCapture videocapture = null;

        private void VideoProcess (object sender, EventArgs e)
        {
            try
            {
                Mat Frame = new Mat(); // 创建Mat对象存储图像帧
                videocapture.Retrieve(Frame);// 从摄像头获取当前帧
                pictureBox1.BackgroundImage = Frame.Bitmap;// PB1显示
                Thread.Sleep(50);
            }
            catch (Exception ex)
            {
                GC.Collect();
            }
        }

        
        // 打开视频
        private void button1_Click(object sender, EventArgs e)
        {
            if (videocapture != null)
                videocapture.Stop();

            videocapture = new VideoCapture(0);
            videocapture.ImageGrabbed += VideoProcess;
            videocapture.Start();
        }

        // 关闭视频
        private void button2_Click(object sender, EventArgs e)
        {
            if (videocapture != null) ;
            videocapture.Stop();

        }
    }
}

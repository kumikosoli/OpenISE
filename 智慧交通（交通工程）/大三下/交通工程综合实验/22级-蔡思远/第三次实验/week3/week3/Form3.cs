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
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;
using Emgu.CV.Util;

namespace week3
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }


        // 根据原始图像识别车道线
        private void DectectLane(Mat originMat)
        {
            // 原始图像表达

            pictureBox9.BackgroundImage = originMat.Bitmap;

            // 转为灰度图像
            Mat grayMat = new Mat();
            CvInvoke.CvtColor(originMat, grayMat, ColorConversion.Bgr2Gray);
            pictureBox10.BackgroundImage = grayMat.Bitmap;

            // 高斯模糊
            Mat bulrMat = new Mat();
            CvInvoke.GaussianBlur(grayMat, bulrMat, new Size(5, 5), 0);
            pictureBox11.BackgroundImage = bulrMat.Bitmap;

            // sobel 边缘检测
            Mat sobelMat = new Mat();
            CvInvoke.Sobel(bulrMat, sobelMat, DepthType.Cv8U, 2, 0);
            pictureBox12.BackgroundImage = sobelMat.Bitmap;

            // 遮蔽区域
            int checkTop = 256;
            VectorOfVectorOfPoint fillPolyPoints = new VectorOfVectorOfPoint();
            fillPolyPoints.Push(new VectorOfPoint(
                new Point[]
                {
                    new Point(0, 0),
                    new Point(originMat.Width, 0),
                    new Point(originMat.Width, originMat.Height - checkTop),
                    new Point(0, originMat.Height - checkTop)
                }));
            CvInvoke.FillPoly(sobelMat, fillPolyPoints, new Bgr(0, 0, 0).MCvScalar);
            pictureBox13.BackgroundImage = sobelMat.Bitmap;

            // 二值化处理
            Mat ThresholdMat = new Mat();
            CvInvoke.Threshold(sobelMat, ThresholdMat, 0, 100, ThresholdType.Otsu);
            pictureBox14.BackgroundImage = ThresholdMat.Bitmap;

            // 形态学滤波
            Mat kernelMat = CvInvoke.GetStructuringElement(ElementShape.Rectangle, new Size(3, 3), new Point(1, 0));
            CvInvoke.Dilate(ThresholdMat, ThresholdMat, kernelMat, new Point(2, 2), 1, BorderType.Default, new MCvScalar(0));
            pictureBox16.BackgroundImage = ThresholdMat.Bitmap;

            //拉普拉斯处理+Canny边缘处理
            Mat cannyMat = new Mat();
            CvInvoke.Laplacian(ThresholdMat, ThresholdMat, ThresholdMat.Depth, 5);
            CvInvoke.Canny(ThresholdMat, cannyMat, 100, 300, 3);

            // 车道线检验
            LineSegment2D[] lines = CvInvoke.HoughLinesP(cannyMat, 1.0, Math.PI / 180, 100, 25, 300);
            Mat laneMat = originMat.Clone();

            foreach (var line in lines)
            {
                CvInvoke.Line(laneMat, line.P1, line.P2, new MCvScalar(0, 0, 255), 2, LineType.AntiAlias);
            }
            pictureBox17.BackgroundImage = laneMat.Bitmap;

        }

        private void button3_Click(object sender, EventArgs e)
        {

            OpenFileDialog ofd = new OpenFileDialog();// 打开对话框
            ofd.Filter = "所有图像文件|*.bmp;*.jpg;*.png";
            ofd.Title = "打开图像文件";
            DialogResult result = ofd.ShowDialog();

            if (result == DialogResult.OK)
            {
                string filename = ofd.FileName;
                Mat originMat = CvInvoke.Imread(filename);
                DectectLane(originMat);

            }
        }
    }
}

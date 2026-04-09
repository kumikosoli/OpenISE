%图像的读取
a=imread('StandardImage/color/airplane.BMP');
b=imread("StandardImage/grayscale/baboon.gif");
c=imread("StandardImage/grayscale/baboon.tiff");
d=imread('StandardImage/color/baboon1.jpg');

%图像的显示
figure,imshow(a),title('BMP格式');  
figure,imshow(b),title('gif格式');
figure,imshow(c),title('tiff格式');
figure,imshow(d),title('jpg格式');

%格式转换与存储:将bmp格式图像转换为jpg格式图像,并进行存储（以下储存为result.jpg)
output_image='result.jpg'; 
imwrite(a,output_image,'jpg');
figure,imshow(output_image),title('bmp格式转换为jpg格式的图像');

%将rgb图像a转化为灰度图
imggray=rgb2gray(a);
figure,imshow(imggray),title('rgb图片转化为灰度图后的图像');
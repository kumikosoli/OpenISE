img1=imread('StandardImage/grayscale/man.BMP');
img2=imread('StandardImage/grayscale/woman1.BMP');
img1=double(img1);
img2=double(img2);
result=zeros(size(img1));   %初始化一个和图像大小相同的矩阵，用于存放结果
speed=0.02;   %渐变切换的速度
for i=0:speed:1
    result=(1-i)*img1+i*img2;
    imshow(uint8(result));
    pause(0.01);   %暂停0.01秒，让图像显示出来
end
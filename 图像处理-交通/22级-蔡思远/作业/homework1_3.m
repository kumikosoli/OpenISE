img=imread("StandardImage/grayscale/peppers.BMP")

%计算直方图数据
data = imhist(img);

%显示直方图
bar(data);
title('图像直方图');
xlabel('灰度级');
ylabel('像素数量');

%直方图均衡化
data_cumsum=cumsum(data);   %计算累积分布函数（CDF）
[m,n]=size(img);
const_a=256/(m*n);
data_cdf=uint8(const_a*data_cumsum);   %归一化累积分布函数
img_eq=img;
for i=1:m
    for j=1:n
        img_eq(i,j)=data_cdf(img(i,j)+1);   %根据累积分布函数映射像素值到新图像img_eq
    end
end
figure,imshow(img),title('原图像')
figure,imshow(img_eq),title('直方图均衡化后图像');


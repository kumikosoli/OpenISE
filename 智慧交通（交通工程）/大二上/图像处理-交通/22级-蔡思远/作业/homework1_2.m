img=imread("StandardImage/grayscale/boats.BMP");
figure,imshow(img),title('原图像');

%图像反转
resulta=255-img;
figure,imshow(resulta),title('图像翻转');

%对数变换
imgb=img-46;
c=45;
imgdouble=double(imgb);
resultb=c*log(1 + imgdouble);
resultb=uint8(resultb);
figure,imshow(resultb),title('对数变换');

%幂次变换
resultc=c*(imgdouble).^0.4;
resultc=uint8(resultc);
figure,imshow(resultc),title('幂次变换');

%阈值化处理
threshold=uint8(128);
[m,n]=size(img);
for row=1:m   %遍历每一个像素
    for col=1:m
        if img(row,col)>=threshold
            img(row,col)=255;
        else
            img(row,col)=0;
        end
    end
end
figure,imshow(img),title('阈值化处理')

%线性拉伸
img=double(img);
img_min=min(img(:));% 获取图像的最大和最小值
img_max=max(img(:));
lower_bound=30;% 设定拉伸的参数
upper_bound=200;
resultd=(img-img_min)/(img_max-img_min)*(upper_bound-lower_bound)+lower_bound;
resultd=uint8(resultd);
figure,imshow(resultd),title('线性拉伸');
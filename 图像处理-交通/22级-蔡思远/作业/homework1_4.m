img=imread("StandardImage/grayscale/lax.BMP");
figure,imshow(img),title('原图像');

%均值滤波
[m,n]=size(img);
template_size=7;   %定义均值滤波模版为7*7
half_template=floor(template_size/2);   %计算模板的一半大小，用于确定模板的中心像素位置
resulte=zeros(m,n);   %创建一个用于存储滤波结果的数组
for i=1:m
    for j=1:n
        pixel_sum=0;   %计算当前像素周围模板范围内的像素均值
        for a=-half_template:half_template
            for b=-half_template:half_template                
                if i+a >= 1 && i+a <= n && j+b >= 1 && j+b <= m   %处理图像边缘情况，超出边界的像素值不参与计算
                    pixel_sum=pixel_sum+double(img(i+a,j+b));
                end
            end
        end        
        resulte(i,j)=round(pixel_sum/(template_size^2));   %计算均值并将结果存储在滤波后的图像中
    end
end
resulte=uint8(resulte);
figure,imshow(resulte),title('均值滤波')

%中值滤波
[c,d]=size(img);
resultf=zeros(c,d);   %创建一个用于存储滤波结果的数组
for i=1:c
    for j=1:d
        neighborpixel=img(max(1,i-1):min(c,i+1),max(1,j-1):min(d,j+1));   %获取当前像素的3*3邻域像素        
        resultf(i,j)=median(neighborpixel(:));   %对邻域内的像素进行排序并取中间值作为当前像素的值
    end
end
resultf=uint8(resultf);
figure,imshow(resultf),title('中值滤波');

%Roberts锐化
roberts_x=[1,0;0,-1];   %定义Roberts算子的卷积核
roberts_y=[0,1;-1,0];
rx=conv2(double(img), roberts_x, 'same');   %进行卷积操作，得到水平和垂直方向上的梯度分量
ry=conv2(double(img), roberts_y, 'same');
resultg=sqrt(rx.^2+ry.^2);   %计算每个像素的梯度幅值，用于突出显示图像的边缘信息
resultg=uint8(resultg);
figure,imshow(resultg),title('Robers锐化');

%Sobel锐化
sobel_x=[-1,-2,-1;0,0,0;1,2,1];   %定义Sobel算子的卷积核
sobel_y=[-1,0,1;-2,0,2;-1,0,1];
sx=conv2(double(img), sobel_x, 'same');   %进行卷积操作，得到水平和垂直方向上的梯度分量
sy=conv2(double(img), sobel_y, 'same');
resulti=sqrt(sx.^2+sy.^2);   %计算每个像素的梯度幅值，用于突出显示图像的边缘信息
resulti=uint8(resulti);
figure,imshow(resulti),title('Sobel锐化');

%Laplacian锐化
lap_x=[0,1,0;1,-4,1;0,1,0];   %定义Laplacian算子的卷积核
lap_y=[1,1,1;1,-8,1;1,1,1];
lx=conv2(double(img), lap_x, 'same');   %进行卷积操作，得到水平和垂直方向上的梯度分量
ly=conv2(double(img), lap_y, 'same');
resultj=sqrt(lx.^2+ly.^2);   %计算每个像素的梯度幅值，用于突出显示图像的边缘信息
resultj=uint8(resultj);
figure,imshow(resultj),title('Laplacian锐化');



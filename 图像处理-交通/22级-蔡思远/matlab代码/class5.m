I = imread('StandardImage/grayscale/IMG_4125_gray.bmp');
I = im2double(I);
M = 2*size(I,1);
N = 2*size(I,2);
u = -M/2:(M/2-1);
v = -N/2:(N/2-1);
[V,U] = meshgrid(v,u);
D = sqrt(U.^2+V.^2);
D0 = 80;
H = double(D<=D0);
J = fftshift(fft2(I,size(H, 1),size(H,2))); % 傅里叶变换
K=J.*H; %滤波
L1 = ifft2(ifftshift(K)); % 傅里叶反变换
L = L1(1:size(I,1),1:size(I, 2)); % L直接截取L1的前1/4
figure;
subplot(121); imshow(I); title("原图");
subplot(122); imshow(L); title("理想低通滤波结果");
figure; mesh(H);

I = imread('StandardImage/grayscale/IMG_4101_gray.bmp');
I = im2double(I);
M = 2*size(I,1); % 滤波器的行数
N = 2*size(I,2); % 滤波器的列数
u = -M/2:(M/2-1);
v = -N/2:(N/2-1);
[V,U] = meshgrid(v,u); % 生成网格的尺寸
D = sqrt(U.^2+V.^2);
H = 1-exp(-(D.^2)./(2*(D0^2))); %设计高斯高通滤波器
J = fftshift(fft2(I,size(H,1),size(H,2))); % 傅里叶变换
K=J.*H; %滤波
L1 = ifft2(ifftshift(K)); % 傅里叶反变换
L = L1(1:size(I,1),1:size(I,2)); % 改变图像大小
figure;
subplot(121);imshow(I);title('原始图像'); %显示原始图像
%显示高斯高通滤波后的图像
subplot(122);imshow(L);title('高斯高通滤波后的图像');
figure; mesh(H);
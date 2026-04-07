% 读取图像
I = imread('StandardImage/color/IMG_4125.jpg');
% 转换为灰度图像
grayImg = rgb2gray(I);
% 计算Roberts边缘
BW1 = edge(grayImg, 'Roberts');
% 计算Sobel边缘
BW2 = edge(grayImg, 'Sobel');
% 计算LoG边缘（使用5x5模板）
log1 = [0 0 -1 0 0; 0 -1 -2 -1 0; -1 -2 16 -2 -1; 0 -1 -2 -1 0; 0 0 -1 0 0];
BW3 = imfilter(double(grayImg), log1);
% 计算Canny边缘
BW4 = edge(grayImg, 'Canny');
% 显示原始图像和边缘检测结果
figure;
subplot(2,3,1), imshow(I), title('原始图像');
subplot(2,3,2), imshow(BW1), title('Roberts边缘');
subplot(2,3,3), imshow(BW2), title('Sobel边缘');
subplot(2,3,4), imshow(BW3, []), title('LoG边缘');
subplot(2,3,5), imshow(BW4), title('Canny边缘');
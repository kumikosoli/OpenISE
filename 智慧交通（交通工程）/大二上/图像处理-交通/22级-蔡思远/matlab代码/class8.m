A = imread("视频帧10766-14000/10766(background).jpg");
A1 = im2gray(A);
B = imread("视频帧10766-14000/11094.jpg");
B1 = im2gray(B);
C = B1-A1;
figure(1);
subplot(3,3,1);
imshow(B);
title('原始帧彩色图片');
subplot(3,3,2);
imshow(A);
title('背景图片');
subplot(3,3,3);
imshow(C);
title('差分运算结果')
D =imbinarize(C);
subplot(3,3,4);
imshow(D);
title('图像分割结果');
E = wiener2(D,[3 3]);
subplot(3,3,5);
imshow(E);
title('去除孤立噪声结果');
se = strel('line',11,90);
% 用垂直线结构元素膨胀图像
F = imdilate(E,se);
subplot(3,3,6);
imshow(F);
title('填补空洞的差图像')
G = bwmorph(F,"bothat");
subplot(3,3,7);
imshow(G);
title('底帽变换结果');
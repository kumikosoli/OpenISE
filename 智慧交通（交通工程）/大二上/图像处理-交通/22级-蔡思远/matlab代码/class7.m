originalBW = imread("StandardImage/grayscale/IMG_4101_gray.bmp");
% 创建一个垂直线形结构元素。
se = strel('line',11,90);
% 用垂直线结构元素膨胀图像并比较结果。
dilatedBW = imdilate(originalBW,se);
% 用垂直线结构元素腐蚀图像并比较结果。
erodedBW = imerode(originalBW,se);
% 用垂直线结构元素进行开运算
afterOpening = imopen(originalBW,se);
% 用垂直线结构元素进行闭运算
closeBW = imclose(originalBW,se);

figure,imshow(dilatedBW),title('膨胀图像');
figure,imshow(erodedBW),title('腐蚀图像');
figure,imshow(afterOpening),title('开运算');
figure,imshow(closeBW),title('闭运算')
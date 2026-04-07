I = imread('车牌图片/plate3(1) 3.jpeg');
% 将彩色图像转换为灰度图像
I1 = rgb2gray(I);
% 使用Roberts算子进行边缘检测
I2 = edge(I1, 'roberts', 0.09, 'both');
% 定义一个垂直方向的结构元素
se = [1; 1; 1];
% 对边缘检测结果进行腐蚀操作，减少噪声
I3 = imerode(I2, se);
% 创建25x25像素的矩形结构元素
se = strel('rectangle', [25, 25]);
% 对图像进行闭运算，连接断开的边缘
I4 = imclose(I3, se);
% 移除小于2000像素的对象
I5 = bwareaopen(I4, 2000);

% 获取处理后图像的尺寸
[y, x, z] = size(I5);
% 将二值图像转换为双精度类型
I6 = double(I5);
% 初始化一个用于存储每行白色像素计数的列向量
Y1 = zeros(y, 1);
% 计算每行的白色像素数量
for i = 1:y
    for j = 1:x
        if (I6(i, j, 1) == 1)
            Y1(i, 1) = Y1(i, 1) + 1;
        end
    end
end
% 找到具有最大白色像素数量的行
[temp, MaxY] = max(Y1);
figure();
% 定位车牌的垂直上边界
PY1 = MaxY;
while ((Y1(PY1, 1) >= 50) && (PY1 > 1))
    PY1 = PY1 - 1;
end
% 定位车牌的垂直下边界
PY2 = MaxY;
while ((Y1(PY2, 1) >= 50) && (PY2 < y))
    PY2 = PY2 + 1;
end

% 提取车牌区域
IY = I(PY1:PY2, :, :);
% 初始化一个用于存储每列白色像素计数的行向量
X1 = zeros(1, x);
% 计算每列的白色像素数量
for j = 1:x
    for i = PY1:PY2
        if (I6(i, j, 1) == 1)
            X1(1, j) = X1(1, j) + 1;
        end
    end
end
% 定位车牌的水平左边界
PX1 = 1;
while ((X1(1, PX1) < 3) && (PX1 < x))
    PX1 = PX1 + 1;
end
% 定位车牌的水平右边界
PX2 = x;
while ((X1(1, PX2) < 3) && (PX2 > PX1))
    PX2 = PX2 - 1;
end
PX1 = PX1 - 1;
PX2 = PX2 + 1;
% 提取车牌最终区域
dw = I(PY1:PY2, PX1:PX2, :);

% 显示原始图像
subplot(3, 1, 1), imshow(I), title('原图');
% 显示标出车牌区域的图像
subplot(3, 1, 2), imshow(I), title('车牌区域');
hold on;
rectangle('Position', [PX1-10, PY1-10, PX2-PX1+20, PY2-PY1+20], 'EdgeColor', 'r', 'LineWidth', 2);
hold off;

% 将提取的车牌区域转换为HSV颜色空间
dw_hsv = rgb2hsv(dw);
% 定义蓝色和黄色的HSV颜色范围
blue_min = [0.5, 0.3, 0.2];
blue_max = [0.7, 1, 1];
yellow_min = [0.1, 0.4, 0.4];
yellow_max = [0.2, 1, 1];
% 计算符合蓝色和黄色阈值的像素数量
blue_mask = (dw_hsv(:, :, 1) >= blue_min(1)) & (dw_hsv(:, :, 1) <= blue_max(1)) & ...
            (dw_hsv(:, :, 2) >= blue_min(2)) & (dw_hsv(:, :, 2) <= blue_max(2)) & ...
            (dw_hsv(:, :, 3) >= blue_min(3)) & (dw_hsv(:, :, 3) <= blue_max(3));
yellow_mask = (dw_hsv(:, :, 1) >= yellow_min(1)) & (dw_hsv(:, :, 1) <= yellow_max(1)) & ...
               (dw_hsv(:, :, 2) >= yellow_min(2)) & (dw_hsv(:, :, 2) <= yellow_max(2)) & ...
               (dw_hsv(:, :, 3) >= yellow_min(3)) & (dw_hsv(:, :, 3) <= yellow_max(3));
% 统计蓝色和黄色像素的数量
num_blue = sum(blue_mask(:));
num_yellow = sum(yellow_mask(:));
% 判断车牌颜色
if num_blue > num_yellow
    resultText = '该车牌为蓝色车牌';
else
    resultText = '该车牌为黄色车牌';
end

subplot(3, 1, 3);
axis off;
text(0.5, 0.5, resultText, 'HorizontalAlignment', 'center', 'VerticalAlignment', 'middle', 'FontSize', 12, 'FontWeight', 'bold');

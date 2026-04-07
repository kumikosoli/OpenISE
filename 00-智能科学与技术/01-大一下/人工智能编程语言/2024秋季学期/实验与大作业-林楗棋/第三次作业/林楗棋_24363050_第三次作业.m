% fx = 2*x1^2 + 4*x2^2 - 6*x1 - 2*x1*x2
% f的梯度 = [4*x1 - 2*x2 - 6; 8*x2 - 2*x1]
% A = [4, -2; -2, 8]

tolarence = 1e-3; % 误差值epsilon
max_iteration = 1000; % 最大循环次数，防止无限循环
init_point = [1; 0]; %起始点
curr_iter = 0;
A = [4, -2; -2, 8]; % A矩阵


while curr_iter < max_iteration
    x_1 = init_point(1); %该点的x_1,x_2值
    x_2 = init_point(2);
    grad = [4 * x_1 - 2 * x_2 - 6; 8 * x_2 - 2 * x_1]; % 求梯度
    alpha =  (grad' * grad) / (grad' * A * grad); %按照公式求alpha值

    if norm(grad) < tolarence
        break
    end
    
    x_1 = x_1 - alpha * grad(1); %计算下一个点
    x_2 = x_2 - alpha * grad(2);
    init_point = [x_1; x_2];
    curr_iter = curr_iter + 1; % 防止无限循环
end

fx = 2*init_point(1)^2 + 4*init_point(2)^2 - 6*init_point(1) - 2*init_point(1)*init_point(2); %计算函数最小值
fprintf("最终点位于(%.3d, %.3d),f(x)最小值为%d\n", init_point(1), init_point(2), fx); % 打印该点位置和函数最小值
fprintf("经过%d次循环\n", curr_iter);
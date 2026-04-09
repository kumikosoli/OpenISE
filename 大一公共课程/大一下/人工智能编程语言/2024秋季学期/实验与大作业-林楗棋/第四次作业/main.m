[rows, true_value] = readExcel();
rows = cell2mat(rows);
tolerance = 1e-500;
K = 2;
max_iteration = 100;

labels      = zeros(208,1); % 用于计算准确度
acc_history = zeros(max_iteration,1); % 用于储存准确度

Indexs = randperm(208, 2); % 随机选取两个索引
centers = rows(Indexs, :); % 取出该行

for i = 1:max_iteration
    for k = 1:208
        dot = rows(k, :);
        dist1 = distance(centers(1, :), dot); % 计算该点到两中心点的距离。
        dist2 = distance(centers(2, :), dot); 
        if dist1 < dist2
            labels(k) = 1;
        else
            labels(k) = 2;
        end
    end % 完成标签分配

    % 开始计算正确率，反转标签值防止随机影响。
    acc1 = mean(labels == true_value); 
    acc2 = mean((3 - labels) == true_value);
    % 记录正确值
    if acc1 > acc2
        acc_history(i) = acc1;
    else
        acc_history(i) = acc2;
    end

    % 寻找新的中心点
    new_center = zeros(2, 60);
    for k = 1:2
       group = find(labels == k); % 找出该簇的所有索引
       expected_center = mean(rows(group, :), 1);
       diffs = rows(group, :) - expected_center;   % 用列表记录簇内每个点离期望点的距离
       dists = sqrt(sum(diffs.^2, 2));          
       [~, minIndex] = min(dists);
       new_center(k, :) = rows(group(minIndex), :);
       Indexs(k) = group(minIndex);
    end

    if distance(new_center(1, :), centers(1, :)) < tolerance && distance(new_center(2, :), centers(2, :)) < tolerance
        centers = new_center;
        acc_history = acc_history(1:i); % 截断记录防止浪费空间
        break
    end
    centers = new_center;
end

finalAcc = acc_history(end);
fprintf('迭代 %d 次后收敛，最终分类准确率：%.2f%%\n', numel(acc_history), finalAcc*100);
disp('最终簇心：');
disp(centers);
plot(acc_history)
function [rows, trueLabels] = readExcel()
 tbl      = readtable('sonar.xls');
 A        = table2array(tbl);      % 208×(60+1)：前208列为特征，第60+1列为真实标签

 % 提取特征部分并拆分成行向量 cell
 features = A(:, 1:end-1);  
 trueLabels = A(:,end);
 [N, D]   = size(features);
 rows     = mat2cell(features, ones(N,1), D);
end    
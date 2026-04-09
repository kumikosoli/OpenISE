digitDatasetPath = fullfile(matlabroot,'toolbox','nnet', 'nndemos','nndatasets','DigitDataset');
imds = imageDatastore(digitDatasetPath, 'IncludeSubfolders',true,'LabelSource','foldernames');
figure, % 随机抽取20张显示
perm = randperm(10000,20);
for i = 1:20
subplot(4,5,i);
imshow(imds.Files{perm(i)});
end
% 计算每个类别中的图像数量
labelCount = countEachLabel(imds);
% 检查imds中第一个图像的大小
img = readimage(imds,1);
% 指定训练集和验证集。训练集中每个类别包含750张图像，其余给验证集。
numTrainFiles = 750;
[imdsTrain,imdsValidation] = splitEachLabel(imds,numTrainFiles,'randomized');

% convolution2dLayer, 创建图像输入层
% convolution2dLayer, 创建卷积层
% batchNormalizationLayer，批量正则化层
% classificationLayer,创建分类层
layers = [imageInputLayer([28 28 1])
convolution2dLayer(3,8,'Padding','same')
batchNormalizationLayer
reluLayer
maxPooling2dLayer(2,'Stride',2)
convolution2dLayer(3,16,'Padding','same')
batchNormalizationLayer
reluLayer
maxPooling2dLayer(2,'Stride',2)
convolution2dLayer(3,32,'Padding','same')
batchNormalizationLayer
reluLayer
fullyConnectedLayer(10)
softmaxLayer
classificationLayer];

options = trainingOptions('sgdm', ...
'InitialLearnRate',0.01, ...
'MaxEpochs',4, ...
'Shuffle','every-epoch', ...
'ValidationData',imdsValidation, ...
'ValidationFrequency',30, ...
'Verbose', false,...
'Plots','training-progress');

net = trainNetwork(imdsTrain, ...
layers,options);

% classify,使用已经训练好的深度神经网络对数据进行分类
YPred = classify(net,imdsValidation);
YValidation = imdsValidation.Labels;
accuracy = sum(YPred == YValidation)/numel(YValidation)






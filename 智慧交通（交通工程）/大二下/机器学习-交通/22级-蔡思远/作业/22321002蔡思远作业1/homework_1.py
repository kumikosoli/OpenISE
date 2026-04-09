import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv('data.csv')
data['diagnosis'] = data['diagnosis'].map({'M': 1, 'B': 0})

# 将csv文件按7：3随机分割为训练集和数据集
train_size = int(len(data) * 0.7)
indices = np.arange(len(data))
np.random.shuffle(indices)
train_indices = indices[:train_size]
test_indices = indices[train_size:]
train_set = data.iloc[train_indices]
test_set = data.iloc[test_indices]

# print(train_set)
# print(test_set)

X = train_set[['radius_mean', 'texture_mean', 'perimeter_mean', 'area_mean', 'smoothness_mean', 'compactness_mean', 'concavity_mean', 'concave points_mean',
               'symmetry_mean', 'fractal_dimension_mean', 'radius_se', 'texture_se', 'perimeter_se', 'area_se', 'smoothness_se',
               'compactness_se', 'concavity_se', 'concave points_se', 'symmetry_se', 'fractal_dimension_se', 'radius_worst', 'texture_worst', 'perimeter_worst',
               'area_worst', 'smoothness_worst', 'compactness_worst', 'concavity_worst', 'concave points_worst', 'symmetry_worst', 'fractal_dimension_worst']].values
y = train_set['diagnosis'].values

X_ = test_set[['radius_mean', 'texture_mean', 'perimeter_mean', 'area_mean', 'smoothness_mean', 'compactness_mean', 'concavity_mean', 'concave points_mean',
               'symmetry_mean', 'fractal_dimension_mean', 'radius_se', 'texture_se', 'perimeter_se', 'area_se', 'smoothness_se',
               'compactness_se', 'concavity_se', 'concave points_se', 'symmetry_se', 'fractal_dimension_se', 'radius_worst', 'texture_worst', 'perimeter_worst',
               'area_worst', 'smoothness_worst', 'compactness_worst', 'concavity_worst', 'concave points_worst', 'symmetry_worst', 'fractal_dimension_worst']].values
y_ = test_set['diagnosis'].values


def sigmoid(z):
    z_safe = np.clip(z, -500, 500) # 避免溢出的安全阈值
    return 1 / (1 + np.exp(-z_safe))

# 损失函数
def cost(y, y_hat):
    m = len(y)
    return -(1/m) * np.sum(y * np.log(y_hat) + (1 - y) * np.log(1 - y_hat))

# 梯度下降，最小化损失函数
def gradient_descent(X, y, lr=0.00003, epochs=len(train_set)):
    m, n = X.shape
    X = np.hstack((np.ones((m, 1)), X))  # 添加偏置项
    w = np.zeros(n + 1)  # 初始化权重
    for epoch in range(epochs):
        z = np.dot(X, w)
        y_hat = sigmoid(z)
        # 损失函数导数
        gradients = (1/m) * np.dot(X.T, (y_hat - y))
        # 更新权重
        w -= lr * gradients
    return w

# 训练模型
w = gradient_descent(X, y)

# 预测函数，输出二分类标签
def predict(X, weights):
    X = np.hstack((np.ones((X.shape[0], 1)), X))  # 添加偏置项
    probabilities = sigmoid(np.dot(X, weights))
    return np.where(probabilities >= 0.5, 1, 0)

# 进行预测
predictions = predict(X_, w)
# print(predictions)

# 计算准确率
accuracy = np.mean(predictions == y_)

# 计算精确率、召回率和F1-score
TP = np.sum((y_ == 1) & (predictions == 1))
TN = np.sum((y_ == 0) & (predictions == 0))
FP = np.sum((y_ == 0) & (predictions == 1))
FN = np.sum((y_ == 1) & (predictions == 0))

precision = TP / (TP + FP) if (TP + FP) != 0 else 0
recall = TP / (TP + FN) if (TP + FN) != 0 else 0
f1_score = 2 * precision * recall / (precision + recall) if (precision + recall) != 0 else 0

print(f"准确率: {accuracy:.3f}")
print(f"查准率: {precision:.3f}")
print(f"查全率: {recall:.3f}")
print(f"F1-score: {f1_score:.3f}")


def predict_probabilities(X, w):
    X = np.hstack((np.ones((X.shape[0], 1)), X))  # 添加偏置项
    probabilities = sigmoid(np.dot(X, w))
    return probabilities

# 使用测试集X_获取概率预测值
probabilities = predict_probabilities(X_, w)

# print(probabilities)

# 计算PR曲线
precision_list = []
recall_list = []
thresholds = np.sort(probabilities) # 将概率从大到小排列，后续作为阈值使用

aupr = 0
prev_recall = 0

for threshold in thresholds:
    predictions = (probabilities >= threshold).astype(int)
    TP = np.sum((y_ == 1) & (predictions == 1))
    FP = np.sum((y_ == 0) & (predictions == 1))
    FN = np.sum((y_ == 1) & (predictions == 0))
    prec = TP / (TP + FP) if (TP + FP) > 0 else 0
    rec = TP / (TP + FN) if (TP + FN) > 0 else 0
    # 计算面积
    if len(recall_list) > 0:
        aupr += (rec - prev_recall) * prec
    prev_recall = rec
    precision_list.append(prec)
    recall_list.append(rec)

plt.figure(figsize=(8, 6))
plt.plot(precision_list, recall_list, label='PR Curve')
plt.title('PR Curve')
plt.ylabel('Recall')
plt.xlabel('Precision')
plt.grid(True)
plt.legend()
plt.show()

print(f"PR曲线下面积(AUPR): {-aupr}")


# 计算ROC曲线
# 排序预测概率，并获取排序后的索引
sorted_indices = np.argsort(probabilities)
sorted_y_ = y_[sorted_indices]
sorted_probabilities = probabilities[sorted_indices]

# 初始化TPR和FPR列表
tpr_list = []
fpr_list = []

auc = 0
prev_fpr = 0

# 获取正例和负例的总数
P = np.sum(y_ == 1)
N = np.sum(y_ == 0)

# 计算每个阈值的TPR和FPR
for threshold in sorted_probabilities:
    predictions = (probabilities >= threshold).astype(int)
    TP = np.sum((y_ == 1) & (predictions == 1))
    FP = np.sum((y_ == 0) & (predictions == 1))
    FN = np.sum((y_ == 1) & (predictions == 0))
    TN = np.sum((y_ == 0) & (predictions == 0))
    TPR = TP / P if P > 0 else 0
    FPR = FP / N if N > 0 else 0
    tpr_list.append(TPR)
    fpr_list.append(FPR)
    # 计算面积
    if len(fpr_list) > 1:
        auc += (FPR - prev_fpr) * TPR
    prev_fpr = FPR

# 画ROC曲线
plt.figure(figsize=(8, 6))
plt.plot(fpr_list, tpr_list, label='ROC Curve')
plt.title('ROC Curve')
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.grid(True)
plt.legend()
plt.show()

print(f"ROC曲线下面积(AUC): {-auc}")


import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# 加载和预处理数据
data = pd.read_csv('data.csv')
data['diagnosis'] = data['diagnosis'].map({'M': 1, 'B': 0})
data = data.sample(frac=1).reset_index(drop=True)

# 划分训练集和测试集
train_size = int(0.7 * len(data))
X_train = data.iloc[:train_size, 1:-1].values  # 假设最后一列之前都是特征
y_train = data.iloc[:train_size, -1].values
X_test = data.iloc[train_size:, 1:-1].values
y_test = data.iloc[train_size:, -1].values

# 标准化特征
X_mean = X_train.mean(axis=0)
X_std = X_train.std(axis=0)
X_train = (X_train - X_mean) / X_std
X_test = (X_test - X_mean) / X_std

def sigmoid(z):
    return 1 / (1 + np.exp(-z))

def cost(theta, X, y):
    m = len(y)
    h = sigmoid(X.dot(theta))
    epsilon = 1e-5  # 避免对0取对数
    return (-1/m) * np.sum(y * np.log(h + epsilon) + (1 - y) * np.log(1 - h + epsilon))

def gradient_descent(X, y, theta, learning_rate, iterations):
    m = len(y)
    cost_history = []
    for _ in range(iterations):
        gradient = X.T.dot(sigmoid(X.dot(theta)) - y) / m
        theta -= learning_rate * gradient
        cost_history.append(cost(theta, X, y))
    return theta, cost_history

def predict_proba(X, theta):
    return sigmoid(X.dot(theta))

def predict(X, theta, threshold=0.5):
    return predict_proba(X, theta) >= threshold

# 添加偏置项
X_train = np.concatenate([np.ones((X_train.shape[0], 1)), X_train], axis=1)
X_test = np.concatenate([np.ones((X_test.shape[0], 1)), X_test], axis=1)

# 初始化参数
theta = np.zeros(X_train.shape[1])

# 训练模型
theta, cost_history = gradient_descent(X_train, y_train, theta, 0.01, 1000)

# 输出成本历史以监控训练过程
plt.plot(cost_history)
plt.xlabel('Iteration')
plt.ylabel('Cost')
plt.title('Cost Function History')
plt.show()

# 进行预测
y_pred = predict(X_test, theta)

# 手动计算性能指标
accuracy = np.mean(y_pred == y_test)
precision = np.sum((y_pred == 1) & (y_test == 1)) / np.sum(y_pred == 1)
recall = np.sum((y_pred == 1) & (y_test == 1)) / np.sum(y_test == 1)
f1 = 2 * precision * recall / (precision + recall)

print("Accuracy:", accuracy)
print("Precision:", precision)
print("Recall:", recall)
print("F1 Score:", f1)

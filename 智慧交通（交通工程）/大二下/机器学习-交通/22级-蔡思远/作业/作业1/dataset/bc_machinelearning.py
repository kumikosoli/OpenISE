import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# 加载和预处理数据
data = pd.read_csv('data.csv')
data['diagnosis'] = data['diagnosis'].map({'M': 1, 'B': 0})
data = data.sample(frac=1).reset_index(drop=True)

# 划分训练集和测试集
train_size = int(0.7 * len(data))
X_train = data.iloc[:train_size, 1:].values
y_train = data.iloc[:train_size, 0].values
X_test = data.iloc[train_size:, 1:].values
y_test = data.iloc[train_size:, 0].values

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
    return (-1 / m) * np.sum(y * np.log(h) + (1 - y) * np.log(1 - h))


def gradient_descent(X, y, theta, learning_rate, iterations):
    m = len(y)
    for _ in range(iterations):
        gradient = X.T.dot(sigmoid(X.dot(theta)) - y) / m
        theta -= learning_rate * gradient
    return theta


def predict_proba(X, theta):
    return sigmoid(X.dot(theta))


def predict(X, theta, threshold=0.5):
    return predict_proba(X, theta) >= threshold


# 添加偏置项
X_train = np.concatenate([np.ones((X_train.shape[0], 1)), X_train], axis=1)
X_test = np.concatenate([np.ones((X_test.shape[0], 1)), X_test], axis=1)

# 初始化参数并训练模型
theta = np.zeros(X_train.shape[1])
theta = gradient_descent(X_train, y_train, theta, 0.01, 1000)

# 进行预测
y_pred_prob = predict_proba(X_test, theta)
y_pred = predict(X_test, theta)


# 手动计算性能指标
def manual_metrics(y_true, y_pred):
    TP = np.sum((y_true == 1) & (y_pred == 1))
    TN = np.sum((y_true == 0) & (y_pred == 0))
    FP = np.sum((y_true == 0) & (y_pred == 1))
    FN = np.sum((y_true == 1) & (y_pred == 0))

    accuracy = (TP + TN) / len(y_true)
    precision = TP / (TP + FP) if TP + FP else 0
    recall = TP / (TP + FN) if TP + FN else 0
    f1 = 2 * precision * recall / (precision + recall) if precision + recall else 0

    return accuracy, precision, recall, f1


accuracy, precision, recall, f1 = manual_metrics(y_test, y_pred)
print("Accuracy:", accuracy)
print("Precision:", precision)
print("Recall:", recall)
print("F1 Score:", f1)


# 绘制PR曲线
def plot_pr_curve(y_true, y_score):
    thresholds = np.sort(y_score)
    precision = []
    recall = []
    for threshold in thresholds:
        y_pred = y_score >= threshold
        TP = np.sum((y_true == 1) & (y_pred == 1))
        FP = np.sum((y_true == 0) & (y_pred == 1))
        FN = np.sum((y_true == 1) & (y_pred == 0))
        prec = TP / (TP + FP) if TP + FP else 0
        rec = TP / (TP + FN) if TP + FN else 0
        precision.append(prec)
        recall.append(rec)
    plt.plot(recall, precision)
    plt.xlabel('Recall')
    plt.ylabel('Precision')
    plt.title('PR Curve')
    plt.show()


plot_pr_curve(y_test, y_pred_prob)


# 绘制ROC曲线
def plot_roc_curve(y_true, y_score):
    thresholds = np.sort(y_score)
    tpr = []
    fpr = []
    for threshold in thresholds:
        y_pred = y_score >= threshold
        TP = np.sum((y_true == 1) & (y_pred == 1))
        FP = np.sum((y_true == 0) & (y_pred == 1))
        TN = np.sum((y_true == 0) & (y_pred == 0))
        FN = np.sum((y_true == 1) & (y_pred == 0))
        tpr.append(TP / (TP + FN) if TP + FN else 0)
        fpr.append(FP / (FP + TN) if FP + TN else 0)
    plt.plot(fpr, tpr)
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('ROC Curve')
    plt.show()


plot_roc_curve(y_test, y_pred_prob)


import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# 定义逻辑回归算法
class LogisticRegression:
    def __init__(self, learning_rate=0.003, iterations=100):
        self.learning_rate = learning_rate  # 学习率
        self.iterations = iterations  # 迭代次数

    def sigmoid(z):
        return 1 / (1 + np.exp(-z))

    def fit(self, X, y):
        # 初始化参数
        self.weights = np.random.randn(X.shape[1])
        self.bias = 0

        # 梯度下降
        for i in range(self.iterations):
            # 计算sigmoid函数的预测值, y_hat = w * x + b
            y_hat = sigmoid(np.dot(X, self.weights) + self.bias)

            # 计算损失函数
            loss = (-1 / len(X)) * np.sum(y * np.log(y_hat) + (1 - y) * np.log(1 - y_hat))

            # 计算梯度
            dw = (1 / len(X)) * np.dot(X.T, (y_hat - y))
            db = (1 / len(X)) * np.sum(y_hat - y)

            # 更新参数
            self.weights -= self.learning_rate * dw
            self.bias -= self.learning_rate * db

            # 打印损失函数值
            if i % 10 == 0:
                print(f"Loss after iteration {i}: {loss}")

    # 预测
    def predict(self, X):
        y_hat = sigmoid(np.dot(X, self.weights) + self.bias)
        y_hat[y_hat >= 0.5] = 1
        y_hat[y_hat < 0.5] = 0
        return y_hat

    # 精度
    def score(self, y_pred, y):
        accuracy = (y_pred == y).sum() / len(y)
        return accuracy

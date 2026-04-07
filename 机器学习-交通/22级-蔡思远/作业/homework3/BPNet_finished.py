# -*- coding: utf-8 -*-
import numpy as np
import pandas as pd
from sklearn.neural_network import MLPRegressor

# 定义激活函数
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

# 1.初始化参数
def initialize(n_x, n_h, n_y):
    np.random.seed(2)

    w1 = np.random.randn(n_h, n_x) * 0.01
    b1 = np.zeros(shape=(n_h, 1))
    w2 = np.random.randn(n_y, n_h) * 0.01
    b2 = np.zeros(shape=(n_y, 1))

    init_paras = {'w1': w1, 'b1': b1, 'w2': w2, 'b2': b2}

    return init_paras
initialize(4, 10, 3)

# 2.前向传播（请补全）
def forward(X, init_paras):
    z1 = np.dot(init_paras['w1'], X) + init_paras['b1']
    g1 = np.tanh(z1)
    z2 = np.dot(init_paras['w2'], g1) + init_paras['b2']
    g2 = sigmoid(z2)
    forward_paras = {'z1':z1, 'g1':g1, 'z2':z2, 'g2':g2}

    return g2, forward_paras

   

# 3.计算代价函数（请补全）
def compute_cost(g2, Y):
    m = Y.shape[1]
    sum1 = np.multiply(np.log(g2), Y) + np.multiply(1 - Y, np.log(1 - g2))
    cost = - np.sum(sum1) / m

    return cost



# 4.反向传播 （请补全）
def backward(init_paras, forward_paras, X, Y):
    m = Y.shape[1]
    w2 = init_paras['w2']
    g1 = forward_paras['g1']
    g2 = forward_paras['g2']

    dz2 = g2 - Y
    dz1 = np.multiply(np.dot(w2.T, dz2), 1 - np.power(g1, 2))
    dw2 = (1/m) * np.dot(dz2, g1.T)
    db2 = (1/m) * np.sum(dz2, axis=1, keepdims=True)
    dw1 = (1/m) * np.dot(dz1, X.T)
    db1 = (1/m) * np.sum(dz1, axis=1, keepdims=True)

    backward_paras = {'dw1':dw1, 'db1':db1, 'dw2':dw2, 'db2':db2}

    return backward_paras

    

# 5.更新参数
def update(init_paras, backward_paras, lr=0.3):
    w1 = init_paras['w1']
    b1 = init_paras['b1']
    w2 = init_paras['w2']
    b2 = init_paras['b2']

    dw1 = backward_paras['dw1']
    db1 = backward_paras['db1']
    dw2 = backward_paras['dw2']
    db2 = backward_paras['db2']

    # 更新参数
    w1 = w1 - dw1 * lr
    b1 = b1 - db1 * lr
    w2 = w2 - dw2 * lr
    b2 = b2 - db2 * lr

    update_paras = {'w1': w1, 'b1': b1, 'w2': w2, 'b2': b2}

    return update_paras


# 6.建立神经网络
def nn_model(X, Y, n_h, n_input, n_output, num_iterations=1, print_cost=False):
    np.random.seed(3)

    n_x = n_input  # 输入层节点数
    n_y = n_output  # 输出层节点数

    # 1.初始化参数
    parameters = initialize(n_x, n_h, n_y)
    # 梯度下降循环
    for i in range(0, num_iterations):
        # 2.前向传播
        a2, forward_paras = forward(X, parameters)
        # 3.计算代价函数
        cost = compute_cost(a2, Y)
        # 4.反向传播
        backward_paras = backward(parameters, forward_paras, X, Y)
        # 5.更新参数
        parameters = update(parameters, backward_paras)

        # 每100次迭代，输出一次代价函数 （请补全）
        if print_cost and i % 1000 == 0:
            print('迭代第%i次，代价函数为：%f' % (i, cost))
        

    return parameters


if __name__ == "__main__":
    # 载入数据集
    data_set = pd.read_csv('iris.csv', header=None)
    X = data_set.iloc[:, 0:4].values.T  # 前四列是特征，T表示转置
    Y = data_set.iloc[:, 4:].values.T

    # 计算参数（请补全）
    parameters = nn_model(X, Y, n_h=10, n_input=4, n_output=3, num_iterations=10000, print_cost=True)
    print(parameters)  # 输出权重和偏置的值









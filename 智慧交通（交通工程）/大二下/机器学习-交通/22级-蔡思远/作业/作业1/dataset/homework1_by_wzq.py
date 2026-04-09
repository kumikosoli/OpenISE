import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.utils import shuffle  # 打乱函数

# 数据处理
origin_data = pd.read_csv("data.csv")  # 导入数据
origin_data = origin_data.loc[:, ~origin_data.columns.str.contains('Unnamed')]  # 去除多余的unnamed列
print(origin_data)
origin_data = shuffle(origin_data)  # 打乱数据
training_set = origin_data[:398].copy()  # 共有569条数据，398条大约为7/10，作为训练集
training_set = training_set.reset_index(drop=True)  # 打乱后重置索引
print(training_set)
test_set = origin_data[398:].copy()  # 剩余171条作为测试集
test_set = test_set.reset_index(drop=True)
print(test_set)

# 定义逻辑斯蒂模型
w = np.zeros(30)  # 系数，初始都设为0
x = np.zeros(30)  # 变量，共有30个

# y_1 = 1 / 1 + np.exp(-z)  # 此时y_1计算的即是y=1的概率
# y_0 = 1 / 1 + np.exp(z)  # 此时y_0计算的即是y=0的概率

# cost函数计算损失
yi = {'M': 1, 'B': 0}  # Yi为标签值,'M'为正类对应1，'B'为负类对应0


# 定义损失函数
def cost(dataset):
    loss = 0  # 损失值最后返回
    num = len(dataset)
    for r in range(len(dataset)):
        num += 1
        for c in range(2, 32):
            x[c - 2] = dataset.iloc[r, c]  # 将对应的变量值赋给x
        # 交叉熵计算损失函数
        z = np.dot(w, x)
        # print(z)
        loss += -np.log(yi[dataset.iloc[r, 1]] * (1 / (1 + np.exp(-z))) +
                        (1 - yi[dataset.iloc[r, 1]]) * (1 / (1 + np.exp(z)) + 1e-5))
    return loss / num


# 定义预测函数
def predict(a):  # 传入一个样本a，返回标签值
    value = ['M', 'B']
    if np.dot(w, a) >= 0:  # 根据逻辑斯蒂模型判断
        return value[0]
    else:
        return value[1]


# 定义梯度下降函数
def gradient_decent():
    w_n = w  # w——new用于返回训练完成的w
    loss_0 = cost(training_set)  # 初始损失
    loss_x = 0
    learning_rate = 0.000015  # 学习率
    for i in range(len(training_set)):  # 总共迭代次数
        for j in range(len(w)):  # 每次迭代中，分别更新三十个参数（更新w）
            grad = 0  # 设置grad为梯度参数
            for k in range(len(training_set)):
                for c in range(2, 32):
                    x[c - 2] = training_set.iloc[k, c]  # 将对应的变量值赋给x
                z = np.dot(w, x)
                grad += training_set.iloc[k, j + 2] * (1 / (1 + np.exp(-z)) - yi[training_set.iloc[k, 1]])  # 计算梯度
            grad /= len(training_set)  # 根据化简的公式计算梯度
            # print(grad)
            w[j] -= learning_rate * grad  # 梯度下降
            loss_x = cost(training_set)  # 每迭代一次w，计算一次损失
        print(w)
        print(cost(training_set))
        if abs(loss_0 - loss_x) < 1e-3:  # 如果前后两次损失非常接近，则停止
            w_n = w
            break
    return w_n


w_new = [-3.87854544e-04, -6.34247903e-04, -2.44427678e-03, -1.04287204e-02,
         -1.31434975e-06, 1.98522983e-07, 2.00646581e-06, 1.06227441e-06,
         -2.53723255e-06, -1.07934465e-06, 2.03352244e-06, -2.06019239e-05,
         1.61913601e-05, 7.54800401e-04, -1.33384994e-07, -1.11346824e-07,
         -4.14887847e-08, -3.90718381e-08, -3.36267296e-07, -5.41770159e-08,
         -5.99817709e-05, -2.87383839e-04, -2.89406960e-04, 8.48869587e-03,
         -4.52370842e-06, -4.46719164e-06, -2.59347815e-06, -1.50935419e-06,
         -9.66038048e-06, -2.87301134e-06]
# w_new = gradient_decent()  # 由于完全训练完成需要时间，这里使用了一组之前训练出的数据来做下面的任务
print("求出的w：")
print(w_new)
# 测试部分
tp = 0  # 真正例
fp = 0  # 假正例
fn = 0  # 假反例
tn = 0  # 真反例
test_set["pre"] = 0  # 为测试集新增一列，用于存放模型的预测值
pre_data = []  # pre_data存放预测值用于设置阈值
for m in range(len(test_set)):
    for n in range(2, 32):
        x[n - 2] = test_set.iloc[m, n]  # 将对应的变量值赋给x
    test_set.loc[m, "pre"] = 1 / (1 + np.exp(-np.dot(w_new, x)))
    pre_data.append(test_set.loc[m, "pre"])
    if yi[test_set.iloc[m, 1]] == 1 and test_set.loc[m, "pre"] >= 0.5:
        tp += 1
    if yi[test_set.iloc[m, 1]] != 1 and test_set.loc[m, "pre"] >= 0.5:
        fp += 1
    if yi[test_set.iloc[m, 1]] == 1 and test_set.loc[m, "pre"] < 0.5:
        fn += 1
    if yi[test_set.iloc[m, 1]] != 1 and test_set.loc[m, "pre"] < 0.5:
        tn += 1
pre_data.sort()
TP = tp + fn
FP = tn + fp
P = tp / (tp + fp)
R = tp / (tp + fn)
print("测试集测试结果：\n准确率：%.2f\n精确率：%.2f\n召回率：%.2f\nF1-score:%.2f" % (
    (tp + tn) / (tp + tn + fp + fn), P, R, 2 * P * R / (P + R)))

# 绘制PR曲线
recall = []  # 查全率
precision = []  # 查准率
aup = 0  # 曲线下面积
for m in range(len(pre_data)):
    t = pre_data[len(pre_data) - m - 1]  # 设定阈值
    tp = 0  # 真正例
    fp = 0  # 假正例
    fn = 0  # 假反例
    tn = 0  # 真假例
    for n in range(len(test_set)):
        if yi[test_set.iloc[n, 1]] == 1 and test_set.iloc[n, 32] >= t:
            tp += 1
        if yi[test_set.iloc[n, 1]] != 1 and test_set.iloc[n, 32] >= t:
            fp += 1
        if yi[test_set.iloc[n, 1]] == 1 and test_set.iloc[n, 32] < t:
            fn += 1
        if yi[test_set.iloc[n, 1]] != 1 and test_set.iloc[n, 32] < t:
            tn += 1
    if tp == 0:
        precision.append(0)  # 更新查准率
    else:
        precision.append(tp / (tp + fp))
    if tp == 0:
        recall.append(0)  # 更新查全率
    else:
        recall.append(tp / (tp + fn))
    aup += precision[m]*(recall[m]-recall[m-1])  # 累加小矩形求面积
plt.figure(1)
plt.title("PR CURVE")
plt.plot(recall, precision)
plt.text(0.3, 0.5, aup)
plt.xlabel('Recall')
plt.ylabel('Precision')

# 绘制ROC曲线
test_sort_set = test_set.sort_values(by=["pre"], ascending=False)  # 按预测值排序
test_sort_set = test_sort_set.reset_index(drop=True)  # 重置索引
tpr = [0]  # 真正例率
fpr = [0]  # 假正例率
p = 0  # 记录真正例数
ne = 0  # 记录假正例数
front = 0  # 记录列表索引用于更新下一坐标
auc = 0  # 曲线下面积，累加得到
le = 0  # 小矩形长
w = 0  # 小矩形宽
for m in range(len(test_sort_set)):  # 依次下降阈值，即依次作为正例
    if yi[test_sort_set.iloc[m, 1]] == 1:  # 真正例
        p += 1
        tpr.append(p / TP)
        fpr.append(fpr[front])  # 分别记录下一点的坐标
        le = tpr[front+1]  # 更新小矩形长
        front += 1
    else:  # 假正例
        ne += 1
        tpr.append(tpr[front])
        fpr.append(ne / FP)
        w = fpr[front+1]-fpr[front]  # 更新小矩形宽
        auc += le * w  # 点每横移一次，累加一次小矩形
        front += 1
plt.figure(2)
plt.title("ROC CURVE")
plt.plot(fpr, tpr)

plt.xlabel('FPR')
plt.ylabel('TPR')
plt.text(0.6, 0.3, auc)  # 图中输出曲线下面积
plt.show()  # 输出图形

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import Perceptron

"""感知机模型"""
# 数据线性可分，二分类数据

class Model:
    def __init__(self):

        # 初始w/b的值
        self.w = np.ones(len(data[0]) - 1, dtype=np.float32)
        self.b = 0  
        self.l_rate = 0.1
      
    # 求y的值
    def sign(self, x, w, b):
        y = np.dot(x, w) + b  
        return y

    
    # 梯度下降法（GD），根据损失函数的梯度，对w，b进行更新（请补全）
    def fit(self, x_train, y_train):
        is_wrong = False
        while not is_wrong:
            wrong_count = 0;
            for d in range(len(x_train)):
                x = x_train[d]
                y = y_train[d]
                if y * self.sign(x, self.w, self.b) <= 0:
                    self.w = self.w + self.l_rate * np.dot(y, x)
                    self.b = self.b + self.l_rate * y
                    wrong_count += 1
            if wrong_count == 0:
                is_wrong = True
        return 'perception model!'



    # 得分
    def score(self):
        pass

# 导入数据集
df = pd.read_csv('Iris.csv', usecols=[1, 2, 3, 4, 5])


"""绘制训练集散点图，观察数据集的线性可分性"""
# 绘制图形的画板尺寸为8*5
plt.figure(figsize=(8, 5))
# 散点图的x坐标、y坐标、标签（请补全三种标签散点分布图可视化）
for species, group in df.groupby('Species'):
    plt.scatter(group['SepalLength'], group['SepalWidth'], alpha=0.8, label=species)
plt.xlabel('SepalLength')
plt.ylabel('SepalWidth')
#  '鸢尾花萼片的长度与宽度的散点分布'
plt.title('Scattered distribution of length and width of iris sepals.')
# 显示标签
plt.legend()
plt.show()


# 取前100条数据中的：前2个特征+标签用于训练
data = np.array(df.iloc[:100, [0, 1, -1]])
# 数据类型转换，为了后面的数学计算
X, y = data[:, :-1], data[:, -1]
y = np.array([1 if i == 'Iris-setosa' else -1 for i in y])


"""感知机模型,开始训练"""
# （请补全感知机模型训练）
perceptron = Model()
# 训练模型
perceptron.fit(X, y)

# 最终参数
print(perceptron.w, perceptron.b)

# 绘图
x_points = np.linspace(4, 7, 10)
y_ = -(perceptron.w[0] * x_points + perceptron.b) / perceptron.w[1]
plt.plot(x_points, y_)
plt.scatter(df[:50]['SepalLength'], df[:50]['SepalWidth'], label='Iris-setosa')
plt.scatter(df[50:100]['SepalLength'], df[50:100]['SepalWidth'], label='Iris-versicolor')
plt.xlabel('SepalLength')
plt.ylabel('SepalWidth')

# '感知机模型训练结果'
plt.title('Training results of Perceptron.')
plt.legend()
plt.show()





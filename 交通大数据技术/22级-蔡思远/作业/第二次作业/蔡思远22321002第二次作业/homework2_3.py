import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
from keras.models import Sequential
from keras.layers import Dense, SimpleRNN


data = pd.read_csv('kwh_train_data.csv')
# print(data)

kwh = data['kwh']
# print(kwh)

# 归一化处理
kwh_norm = kwh/max(kwh)
# print(kwh_norm)

# 原始数据可视化
fig1 = plt.figure(figsize=(16,8))
plt.plot(kwh)
plt.title('kwh')
plt.xlabel('time')
plt.ylabel('kwh')
plt.show()

# 定义x和y; 提取x和y
def extract_data(data, time_step):
    X = []
    y = []
    for i in range(len(data)-time_step):
        X.append([a for a in data[i:i + time_step]])
        y.append(data[i + time_step])
    X = np.array(X)
    y = np.array(y)
    X = X.reshape(X.shape[0], X.shape[1], 1)
    return X, y

time_step = 8
X, y = extract_data(kwh_norm, time_step)
# print(X[0])
# print(y)

# 建立模型
model = Sequential()
# 增加RNN层，输出有5个神经元，使用relu作为激活函数
model.add(SimpleRNN(units=5, input_shape=(time_step, 1,), activation='relu'))
# 增加输出层，使用线性模型
model.add(Dense(units=1,activation='linear'))
# 配置训练数据，优化器adam，损失函数
model.compile(optimizer='adam', loss='mean_squared_error')
# model.summary()

# 训练模型，每次提取30个样本，迭代100次
model.fit(X, y, batch_size=30, epochs=100)

# 在训练集上进行预测（并将归一化数据还原）
y_train_predict = model.predict(X) * max(kwh)
y_train = y * max(kwh)
# print((y_train_predict))
# print(y_train)

# 训练集预测结果可视化
fig2 = plt.figure(figsize=(30,8))
plt.plot(y_train, label='real_kwh', color='blue')
plt.plot(y_train_predict, label='predict_kwh', color='red')
plt.title('predict_kwh')
plt.xlabel('time')
plt.ylabel('kwh')
plt.legend()
plt.show()

# 基于训练好的模型，对测试集进行预测
data_test = pd.read_csv('kwh_test_data.csv')
kwh_test = data_test['kwh']
kwh_test_norm = kwh_test/max(kwh)
# 提取X和y
X_test_norm, y_test_norm = extract_data(kwh_test_norm, time_step)

# 在测试集上进行预测
y_test_predict = model.predict(X_test_norm) * max(kwh)
y_test = y_test_norm * max(kwh)

# 测试集预测结果可视化
fig2 = plt.figure(figsize=(30,8))
plt.plot(y_test, label='real_kwh', color='yellow')
plt.plot(y_test_predict, label='predict_kwh', color='green')
plt.title('predict_kwh')
plt.xlabel('time')
plt.ylabel('kwh')
plt.legend()
plt.show()

# 特别的现象
result_y_test = np.array(y_test).reshape(-1,1)
result_y_test_predict = y_test_predict
result = np.concatenate((result_y_test,result_y_test_predict),axis=1)
result = pd.DataFrame(result, columns=['real_kwh_test', 'predict_kwh_test'])
result.to_csv('kwh_predict.csv')

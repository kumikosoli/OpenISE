import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
from keras.models import Sequential
from keras.layers import Dense, SimpleRNN

# 读取CSV文件
data = pd.read_csv('2022_12_1-2022_12_15.csv')

# 提取并归一化kwh数据
kwh = data['kwh']
kwh_norm = kwh / max(kwh)

# 按7比3划分训练集和测试集
train_size = int(len(kwh_norm) * 0.7)
test_size = len(kwh_norm) - train_size

train_data = kwh_norm[:train_size]
test_data = kwh_norm[train_size:]

print(f"训练集大小: {len(train_data)}")
print(f"测试集大小: {len(test_data)}")

# 原始数据可视化
fig1 = plt.figure(figsize=(16, 8))
plt.plot(kwh)
plt.title('kwh')
plt.xlabel('time')
plt.ylabel('kwh')
plt.show()

# 定义x和y; 提取x和y
def extract_data(data, time_step):
    X = []
    y = []
    for i in range(len(data) - time_step):
        X.append([a for a in data[i:i + time_step]])
        y.append(data[i + time_step])
    X = np.array(X)
    y = np.array(y)
    X = X.reshape(X.shape[0], X.shape[1], 1)
    return X, y

time_step = 8
X_train, y_train = extract_data(train_data, time_step)
X_test, y_test = extract_data(test_data, time_step)

# 打印训练集和测试集样本
print(f"X_train shape: {X_train.shape}")
print(f"y_train shape: {y_train.shape}")
print(f"X_test shape: {X_test.shape}")
print(f"y_test shape: {y_test.shape}")

# 建立模型
model = Sequential()
model.add(SimpleRNN(units=5, input_shape=(time_step, 1), activation='relu'))
model.add(Dense(units=1, activation='linear'))
model.compile(optimizer='adam', loss='mean_squared_error')

# 训练模型
model.fit(X_train, y_train, batch_size=30, epochs=100)

# 在训练集上进行预测（并将归一化数据还原）
y_train_predict = model.predict(X_train) * max(kwh)
y_train = y_train * max(kwh)

# 训练集预测结果可视化
fig2 = plt.figure(figsize=(30, 8))
plt.plot(y_train, label='real_kwh', color='blue')
plt.plot(y_train_predict, label='predict_kwh', color='red')
plt.title('predict_kwh')
plt.xlabel('time')
plt.ylabel('kwh')
plt.legend()
plt.show()

# 在测试集上进行预测（并将归一化数据还原）
y_test_predict = model.predict(X_test) * max(kwh)
y_test = y_test * max(kwh)

# 测试集预测结果可视化
fig2 = plt.figure(figsize=(30, 8))
plt.plot(y_test, label='real_kwh', color='yellow')
plt.plot(y_test_predict, label='predict_kwh', color='green')
plt.title('predict_kwh')
plt.xlabel('time')
plt.ylabel('kwh')
plt.legend()
plt.show()

import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import Dense, SimpleRNN
import matplotlib.pyplot as plt

# 加载数据
data = pd.read_csv('2022_12_1-2022_12_15.csv')
data['time_new'] = pd.to_datetime(data['time_new'], format='%Y/%m/%d %H:%M')
data.set_index('time_new', inplace=True)

# 规范化数据
scaler = MinMaxScaler(feature_range=(0, 1))
data['kwh'] = scaler.fit_transform(data[['kwh']])

# 创建时间序列数据集
def create_dataset(data, look_back=288):
    X, Y = [], []
    for i in range(len(data) - look_back):
        a = data[i:(i + look_back), 0]
        X.append(a)
        Y.append(data[i + look_back, 0])
    return np.array(X), np.array(Y)

# 准备输入输出数据
dataset = data['kwh'].values
dataset = dataset.reshape(-1, 1)
X, y = create_dataset(dataset, 288)
X = X.reshape(X.shape[0], X.shape[1], 1)  # RNN需要的形状

# 划分数据集
split_percent = 0.80
split = int(split_percent * len(X))
X_train = X[:split]
y_train = y[:split]
X_test = X[split:]
y_test = y[split:]

# 创建和编译模型
model = Sequential()
model.add(SimpleRNN(units=50, activation='tanh', input_shape=(288, 1)))
model.add(Dense(units=1))
model.compile(loss='mean_squared_error', optimizer='adam')

# 训练模型
model.fit(X_train, y_train, epochs=100, batch_size=1, verbose=1)

# 预测新数据
prediction = model.predict(X_test)
prediction = scaler.inverse_transform(prediction)
y_test = scaler.inverse_transform(y_test.reshape(-1, 1))

# # 输出预测结果与实际结果的比较
# for p, true in zip(prediction.flatten(), y_test.flatten()):
#     print(f"预测: {p:.2f}, 实际: {true:.2f}")

# 预测未来24小时数据的函数
def predict_next_24_hours(model, last_sequence, num_prediction_steps):
    prediction_list = last_sequence.copy()
    for _ in range(num_prediction_steps):
        x = prediction_list[-288:]  # 取最后288个数据作为输入
        x = x.reshape((1, 288, 1))  # 调整形状以符合模型输入要求
        out = model.predict(x)[0,0]  # 进行预测
        prediction_list = np.append(prediction_list, out)  # 添加预测结果
    return prediction_list[-num_prediction_steps:]  # 返回预测的24小时数据

# 获取最后一个序列作为预测的起始点
last_sequence = dataset[-288:, 0]

# 使用模型预测未来24小时的能耗数据
predictions_24h = predict_next_24_hours(model, last_sequence, 288)  # 24小时的数据点

# 将预测的数据逆规范化
predictions_24h_rescaled = scaler.inverse_transform(predictions_24h.reshape(-1, 1))

# 生成时间序列，从最后一个时间点开始，每5分钟一个点
last_time = data.index[-1]
time_series = pd.date_range(last_time, periods=288 + 1, freq='5T')[1:]  # 加1因为pd.date_range包括开始时间

# 绘制预测结果
plt.figure(figsize=(12, 6))
plt.plot(time_series, predictions_24h_rescaled, label='Predicted kwh')
plt.title('24 Hours Energy Consumption Prediction')
plt.xlabel('Time')
plt.ylabel('kWh')
plt.xticks(rotation=45)
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
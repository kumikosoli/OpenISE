import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from matplotlib.dates import DateFormatter
from matplotlib import font_manager
from PIL import Image

font_manager.fontManager.addfont('/Users/caisiyuan/anaconda3/lib/python3.11/site-packages/matplotlib/mpl-data/fonts/ttf/SimHei.ttf')
plt.rcParams['font.sans-serif']=['SimHei'] # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus']=False # 用来正常显示负号

data = pd.read_csv('ICData.csv')

data['交易时间'] = pd.to_datetime(data['交易时间'])
data['小时'] = data['交易时间'].dt.hour


# 1、时间序列分析
# 绘制线图展示一天内每小时的刷卡频率
hour_freq = data.groupby('小时').size()
plt.figure(figsize=(10, 6))
plt.plot(hour_freq.index, hour_freq.values, marker='o')
plt.xlabel('小时')
plt.ylabel('刷卡频率')
plt.title('一天内每小时的刷卡频率')
plt.show()

# 堆叠柱状图展示不同线路一天不同小时的刷卡频率
top10_routes = data['线路号'].value_counts().index[:10]
selected_data = data[data['线路号'].isin(top10_routes)]
route_hourly_freq = selected_data.groupby(['线路号', '小时']).size().unstack(fill_value=0)
route_hourly_freq.plot(kind='bar', stacked=True, figsize=(10,8))
plt.xlabel('线路号')
plt.ylabel('刷卡频率')
plt.title('10个线路一天不同小时的刷卡频率')
plt.legend(title='小时')
plt.show()


# 2、线路与站点分析
# 展示哪些线路的刷卡频率最高（取最高刷卡频率的10条线路）
top10_route_freq = data['线路号'].value_counts().head(10)
top10_route_freq.plot(kind='bar', figsize=(10, 6))
plt.xlabel('线路号')
plt.ylabel('刷卡频率')
plt.title('刷卡频率最高的10个线路')
plt.show()

# 展示上车人数最多的站点
boarding_passengers = data['上车站点'].value_counts()
plt.figure(figsize=(12,6))
boarding_passengers.plot(kind='bar', color='skyblue')
plt.xlabel('站点')
plt.ylabel('上车人数')
plt.title('上车人数站点统计')
plt.show()

# 展示下车人数最多的站点
alighting_passengers = data['下车站点'].value_counts()
plt.figure(figsize=(12,6))
alighting_passengers.plot(kind='bar', color='lightgreen')
plt.xlabel('站点')
plt.ylabel('下车人数')
plt.title('下车人数站点统计')
plt.show()


# 站点分析热力图：颜色越深，表示从一个站点（y轴）到另一个站点（x轴）的乘客数量越多，这可能表示存在换乘关系。
# 换乘站点往往在一天中会有大量的上车和下车行为，因此如果一个站点的上车人数和下车人数之间的差异较大，那么这个站点可能就是一个换乘站点。
transfer_difference = abs(boarding_passengers - alighting_passengers)
pivot_table = pd.pivot_table(data, values='交易卡号', index='上车站点', columns='下车站点', aggfunc='count', fill_value=0)
normalized_pivot_table = (pivot_table - np.min(pivot_table.values)) / (np.max(pivot_table.values) - np.min(pivot_table.values))
# 绘制热力图
plt.figure(figsize=(15,10))
sns.heatmap(normalized_pivot_table, cmap='coolwarm')
plt.title('可能的换乘站点分析')
plt.xlabel('下车站点')
plt.ylabel('上车站点')
plt.show()


# 3、车辆与驾驶员分析：
# 只选取10辆车辆的数据进行绘制
selected_vehicles = data['车辆编号'].value_counts().index[:10]
selected_data = data[data['车辆编号'].isin(selected_vehicles)]
plt.figure(figsize=(10,5))
sns.boxplot(x='车辆编号', y='小时', data=selected_data)
plt.title('10辆车辆一天中的工作时间分布')
plt.show()
# 只选取10位驾驶员的数据进行绘制
selected_drivers = data['驾驶员编号'].value_counts().index[:10]
selected_data = data[data['驾驶员编号'].isin(selected_drivers)]
plt.figure(figsize=(10,5))
sns.boxplot(x='驾驶员编号', y='小时', data=selected_data)
plt.title('10位驾驶员一天中的工作时间分布')
plt.show()

# 不同运营公司的车辆运行频率和驾驶员的工作时长对比
data['交易日期'] = data['交易时间'].dt.date
vehicle_freq = data['运营公司编号'].value_counts()
driver_worktime = data.groupby(['运营公司编号', '驾驶员编号', '交易日期']).agg({'交易时间':[np.min, np.max]})
driver_worktime.columns = ["_".join(x) for x in driver_worktime.columns.ravel()]
# 将工作时长转换为小时
driver_worktime['工作时长'] = (driver_worktime['交易时间_amax'] - driver_worktime['交易时间_amin']).dt.seconds / 3600
driver_worktime = driver_worktime.groupby('运营公司编号')['工作时长'].sum()
df = pd.DataFrame({'车辆运行频率': vehicle_freq, '驾驶员工作时长': driver_worktime})
fig, ax1 = plt.subplots(figsize=(10, 6))
ax2 = ax1.twinx()
df.车辆运行频率.plot(kind='bar', color='skyblue', ax=ax1, position=1)
df.驾驶员工作时长.plot(kind='bar', color='lightgreen', ax=ax2, position=0)
ax1.legend(loc='upper left')
ax2.legend(loc='upper right')
ax1.set_xlabel('运营公司编号')
ax1.set_ylabel('车辆运行频率')
ax2.set_ylabel('驾驶员工作时长')
plt.show()


# 交易类型分析：
# 展示不同交易类型刷卡频率的饼图
transaction_freq = data['交易类型'].value_counts()
plt.figure(figsize=(10,6))
plt.pie(transaction_freq, labels=transaction_freq.index, autopct='%1.1f%%')
plt.title('不同交易类型的刷卡频率')
plt.show()
print('''
由饼图可推测得：
交易类型6：普通卡
交易类型188：老人免费卡
交易类型191：老人优惠卡
交易类型8：学生卡
''')

# 交易类型与线路之间的关联
# 先找出交易量最大的10个线路
top10_routes = data['线路号'].value_counts().index[:10]
selected_data = data[data['线路号'].isin(top10_routes)]
grouped = selected_data.groupby(['线路号', '交易类型']).size().unstack()
grouped.plot(kind='bar', figsize=(10,6))
plt.title('10个线路不同交易类型的刷卡频率')
plt.xlabel('线路号')
plt.ylabel('刷卡频率')
plt.show()

# 交易类型与时间之间的关联
grouped = data.groupby(['小时', '交易类型']).size().unstack()
grouped.plot(kind='bar', figsize=(10,6))
plt.title('不同时间不同交易类型的刷卡频率')
plt.xlabel('小时')
plt.ylabel('刷卡频率')
plt.show()

img = Image.open('homework4_image.jpg')
img.show()





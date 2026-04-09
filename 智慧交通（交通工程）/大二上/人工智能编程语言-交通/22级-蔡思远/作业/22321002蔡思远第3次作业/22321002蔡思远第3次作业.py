import pandas as pd
import numpy as np
import math
from scipy.stats import tstd

# 写入csv文件
df = pd.read_csv('ICData.csv', parse_dates=['交易时间'])
# 从交易时间列中提取小时
df['hour'] = df['交易时间'].dt.hour
# 分别计算早上7点前和晚上10点之后的公共交通上车刷卡量
morning_rush = df[df['hour']<7].shape[0]
night_rush = df[df['hour']>22].shape[0]
print('要求1：')
print(f'早上7点前上车刷卡量： {morning_rush}')
print(f'晚上10点后上车刷卡量： {night_rush}')

# 构造乘客搭乘站点数分析函数
def calc_line_passenger(df, line_no):
    line_data = df[df['线路号'] == line_no]
    line_data['站点数'] = abs(line_data['上车站点'] - line_data['下车站点'])
    avg_stop = line_data['站点数'].mean()
    std_stop = line_data['站点数'].std()
    # 将所得值四舍五入保留两位小数
    avg_stop = round(avg_stop,2)
    std_stop = round(std_stop,2)
    return avg_stop, std_stop
print('要求2：')
avg, std = calc_line_passenger(df, 1101)
print(f'线路1101的乘客平均公交搭乘站点数为: {avg}, 标准差为: {std}')
avg, std = calc_line_passenger(df, 1117)
print(f'线路1117的乘客平均公交搭乘站点数为: {avg}, 标准差为: {std}')
avg, std = calc_line_passenger(df, 1106)
print(f'线路1106的乘客平均公交搭乘站点数为: {avg}, 标准差为: {std}')
avg, std = calc_line_passenger(df, 1112)
print(f'线路1112的乘客平均公交搭乘站点数为: {avg}, 标准差为: {std}')
avg, std = calc_line_passenger(df, 1114)
print(f'线路1114的乘客平均公交搭乘站点数为: {avg}, 标准差为: {std}')
avg, std = calc_line_passenger(df, 1109)
print(f'线路1109的乘客平均公交搭乘站点数为: {avg}, 标准差为: {std}')
avg, std = calc_line_passenger(df, 1113)
print(f'线路1113的乘客平均公交搭乘站点数为: {avg}, 标准差为: {std}')
avg, std = calc_line_passenger(df, 1128)
print(f'线路1128的乘客平均公交搭乘站点数为: {avg}, 标准差为: {std}')
avg, std = calc_line_passenger(df, 1111)
print(f'线路1111的乘客平均公交搭乘站点数为: {avg}, 标准差为: {std}')

# 计算高峰小时刷卡量和公交刷卡量的高峰小时系数（PHF5和PHF15）
print('要求3：')
# 通过按小时分组计算每小时的刷卡数量
card_by_hour = df.groupby(df['交易时间'].dt.hour).size()
max_hour = card_by_hour.idxmax()
max_card = card_by_hour.max()
# 计算分钟数，将小时转化为分钟
df['minute'] = df['交易时间'].dt.minute + 60 * df['交易时间'].dt.hour
# 通过对df按照minute列进行分组，并计算滚动窗口大小为5和15的刷卡数量的最大值
peak_5min_traffic = df.groupby('minute').size().rolling(5).sum().max()
peak_15min_traffic = df.groupby('minute').size().rolling(15).sum().max()
# 计算PHF5和PHF15
PHF5 = max_card / (12 * peak_5min_traffic)
PHF15 = max_card / (4 * peak_15min_traffic)
print(f'高峰小时刷卡量PHT: {max_card}。公交刷卡量的高峰小时系数PHF5: {PHF5}，PHF15: {PHF15}')

import os
# 新建名为bus_information的文件夹
os.makedirs('bus_information', exist_ok=True)
# 运用for循环将线路号为1101-1120的公交车信息转为txt文件保存至文件夹中
for line_no in range(1101, 1121):
    line_data = df[df['线路号'] == line_no]
    with open(f'bus_information/route_{line_no}.txt', 'w') as f:
        f.write(f'Route Number: {line_no}\n')
        f.write(f'Drivers: {line_data["驾驶员编号"].unique()}\n')
        f.write(f'Vehicles: {line_data["车辆编号"].unique()}\n')
print('''要求4：
已将信息输出为20个txt文档，并保存到bus_information文件夹中''')
print('''要求5：
分析搭载乘客情况：''')
# 按出现次数进行排序
top_10_drivers = df['驾驶员编号'].value_counts().head(10).index.tolist()
top_10_lines = df['线路号'].value_counts().head(10).index.tolist()
top_10_stops = df['上车站点'].value_counts().head(10).index.tolist()
top_10_vehicles = df['车辆编号'].value_counts().head(10).index.tolist()

print('服务乘客人次最多的10个司机：驾驶员编号')
for driver in top_10_drivers:
    print(driver)
print('服务乘客人次最多的10条线路：线路号')
for line in top_10_lines:
    print(line)
print('服务乘客人次最多的10个站点：上车站点')
for stop in top_10_stops:
    print(stop)
print('服务乘客人次最多的10台车辆：车辆编号')
for vehicle in top_10_vehicles:
    print(vehicle)



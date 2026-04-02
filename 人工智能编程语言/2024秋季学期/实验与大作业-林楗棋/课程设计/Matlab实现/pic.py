
import json
import matplotlib.pyplot as plt
import os

os.chdir(os.path.dirname(__file__))  # 切换工作目录到脚本所在目录
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
re = './population_data'  # 数据存储在一个名为 population_data 的文件夹中
file_paths = [
    f'{re}/g0.json',
    f'{re}/g1.json',
    f'{re}/g2.json',
    f'{re}/g3.json',
    f'{re}/g4.json'
]

data = {}

for idx, path in enumerate(file_paths):
    with open(path, 'r') as f:
        content = json.load(f)
        generations = [item['generation'] for item in content['generations']]
        avg_value = [item['avg_value'] for item in content['generations']]
        data[f'g{idx}'] = {
            'generations': generations,
            'avg_value': avg_value
        }

plt.figure(figsize=(10, 6))

for label, values in data.items():
    plt.plot(
        values['generations'],
        values['avg_value'],
        label=label
    )

plt.xlabel('种群代数')
plt.ylabel('函数平均值')
plt.title('比较五次运行的函数平均值随代数变化(Matlab)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

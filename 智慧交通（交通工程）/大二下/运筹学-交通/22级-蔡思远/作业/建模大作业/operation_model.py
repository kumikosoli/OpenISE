import pandas as pd
import pulp

# 读取Excel文件
file_path = 'op_model.xlsx'
df = pd.read_excel(file_path)

# 创建一个线性规划问题，设定为最大化问题
prob = pulp.LpProblem("Maximize_Influence", pulp.LpMaximize)

# 定义决策变量
up_zhu = df['up主'].tolist()
video_types = ['定制视频', '植入视频', '动态直发', '动态转发']
vars = {up: {vt: pulp.LpVariable(f'{up}_{vt}', lowBound=0, upBound=df.loc[i, f'{vt}数量上限'] if pd.notna(df.loc[i, f'{vt}数量上限']) else 0, cat='Integer')
             for vt in video_types} for i, up in enumerate(up_zhu)}

# 定义目标函数：最大化总影响力
prob += pulp.lpSum([df.loc[i, f'{vt}影响力'] * vars[up][vt] for i, up in enumerate(up_zhu) for vt in video_types]), "Total_Influence"

# 添加预算约束
budget = 10000000  # 总预算为1000万元
prob += pulp.lpSum([df.loc[i, f'{vt}价格'] * vars[up][vt] for i, up in enumerate(up_zhu) for vt in video_types]) <= budget, "Budget_Constraint"

# 添加每个UP主每种视频类型的数量上限约束
for i, up in enumerate(up_zhu):
    for vt in video_types:
        # 处理 NaN 情况，如果数量上限为 NaN，则将其视为 0
        upper_bound = df.loc[i, f'{vt}数量上限'] if pd.notna(df.loc[i, f'{vt}数量上限']) else 0
        prob += vars[up][vt] <= upper_bound, f"{up}_{vt}_Limit_{i}"

# 求解问题
solver = pulp.COIN_CMD(path='/Users/caisiyuan/anaconda3/bin/cbc')  # 使用绝对路径
prob.solve()

# 输出结果
solution = {
    "UP主": [],
    "广告类型": [],
    "投放数量": []
}

for up in up_zhu:
    for vt in video_types:
        solution["UP主"].append(up)
        solution["广告类型"].append(vt)
        solution["投放数量"].append(pulp.value(vars[up][vt]))

solution_df = pd.DataFrame(solution)
total_influence = pulp.value(prob.objective)
total_cost = sum(df.loc[i, f'{vt}价格'] * pulp.value(vars[up][vt]) for i, up in enumerate(up_zhu) for vt in video_types)

print(solution_df)
print("Total Influence = ", total_influence)
print("Total Cost = ", total_cost)
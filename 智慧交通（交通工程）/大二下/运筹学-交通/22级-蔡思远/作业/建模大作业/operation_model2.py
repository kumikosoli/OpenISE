import pulp
import pandas as pd

# 读取Excel文件
file_path = "op_model6.csv"
df = pd.read_csv(file_path)
df.fillna(0, inplace=True)

# 提取所需的列
up = df['up_zhu'].astype(str)  # 确保所有值为字符串类型
up_bound1 = df['1_video_limit']
up_bound2 = df['2_video_limit']
up_bound3 = df['1_text_limit']
up_bound4 = df['2_text_limit']
influ1 = df['1_video_influ']
influ2 = df['2_video_influ']
influ3 = df['1_text_influ']
influ4 = df['2_text_influ']
price1 = df['1_video_price']
price2 = df['2_video_price']
price3 = df['1_text_price']
price4 = df['2_text_price']

# 创建一个线性规划问题，设定为最大化问题
prob = pulp.LpProblem("Maximize_Influence", pulp.LpMaximize)

# 初始化一个空字典
variables = {}
# 循环赋值
for i in range(1, 134):
    # 生成合法的变量名
    up_name = ''.join(e for e in up[i - 1] if e.isalnum() or e == '_').strip('_')
    up_name = f"up_{i}_{up_name}"
    # 确保变量名唯一且合法
    var_name1 = f'{up_name}_1_video_num'
    var_name2 = f'{up_name}_2_video_num'
    var_name3 = f'{up_name}_1_text_num'
    var_name4 = f'{up_name}_2_text_num'

    # 调试打印变量名
    print(f'Creating variables: {var_name1}, {var_name2}, {var_name3}, {var_name4}')

    variables[f"x{i}_1"] = pulp.LpVariable(var_name1, 0, up_bound1[i - 1], pulp.LpContinuous)
    variables[f"x{i}_2"] = pulp.LpVariable(var_name2, 0, up_bound2[i - 1], pulp.LpContinuous)
    variables[f"x{i}_3"] = pulp.LpVariable(var_name3, 0, up_bound3[i - 1], pulp.LpContinuous)
    variables[f"x{i}_4"] = pulp.LpVariable(var_name4, 0, up_bound4[i - 1], pulp.LpContinuous)

print(variables)
# # 定义目标函数
# objective = pulp.lpSum([
#     (variables[f"x{j}_1"] * influ1[j - 1]) +
#     (variables[f"x{j}_2"] * influ2[j - 1]) +
#     (variables[f"x{j}_3"] * influ3[j - 1]) +
#     (variables[f"x{j}_4"] * influ4[j - 1])
#     for j in range(1, 134)
# ])
# prob += objective
#
# # 添加价格限制约束
# limit = pulp.lpSum([
#     (variables[f"x{n}_1"] * price1[n - 1]) +
#     (variables[f"x{n}_2"] * price2[n - 1]) +
#     (variables[f"x{n}_3"] * price3[n - 1]) +
#     (variables[f"x{n}_4"] * price4[n - 1])
#     for n in range(1, 134)
# ])
# prob += limit <= 10000000
#
# # 写入模型
# prob.writeLP("operation_model8")
#
# # 求解问题
# prob.solve(pulp.GLPK_CMD())
#
# # 输出结果，只保留非0值的变量
# print('\n', 'status:', pulp.LpStatus[prob.status], '\n')
#
# for m in range(1, 134):
#     if variables[f"x{m}_1"].varValue != 0:
#         print(variables[f"x{m}_1"].name, "=", variables[f"x{m}_1"].varValue)
#     if variables[f"x{m}_2"].varValue != 0:
#         print(variables[f"x{m}_2"].name, "=", variables[f"x{m}_2"].varValue)
#     if variables[f"x{m}_3"].varValue != 0:
#         print(variables[f"x{m}_3"].name, "=", variables[f"x{m}_3"].varValue)
#     if variables[f"x{m}_4"].varValue != 0:
#         print(variables[f"x{m}_4"].name, "=", variables[f"x{m}_4"].varValue)
#
# print("Max_Influence", pulp.value(prob.objective))
#
#
#
#
#
#
#

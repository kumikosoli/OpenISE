import pandas as pd

def match(str1, str2):  # 定义一个匹配函数检测两个车牌(字符串)是否匹配
    if len(str1) == len(str2):
        flag = 0  # 记录车牌是否匹配成功，若有连续三个字符匹配，则认为两车牌匹配
        m = 0  # i指向两个待匹配车牌的第一个字符
        while m + 2 < len(str1):  # 最多从倒数第三个字符开始匹配
            num = 0
            for times in range(3):
                if str1[m + times] != str2[m + times]:
                    m = m + times + 1
                    num = 0
                    break
                num += 1
            if num == 3:
                flag = 1
                break  # 已匹配成功，不需在匹配
        return flag  # 匹配返回1，否则返回0
    else:
        return 0


# 导入数据：
# cutx_usual/high：断面x平峰/高峰时的数据
cut1_usual = pd.read_csv(r'车辆调查表_断面1_平峰.csv')
cut4_usual = pd.read_csv(r'车辆调查表_断面4_平峰.csv')
cut6_usual = pd.read_csv(r'车辆调查表_断面6_平峰.csv')
cut8_usual = pd.read_csv(r'车辆调查表_断面8_平峰.csv')
cut1_high = pd.read_csv(r'车辆调查表_断面1_高峰.csv')
cut4_high = pd.read_csv(r'车辆调查表_断面4_高峰.csv')
cut6_high = pd.read_csv(r'车辆调查表_断面6_高峰.csv')
cut8_high = pd.read_csv(r'车辆调查表_断面8_高峰.csv')


# 平峰
# 新dataframe存储合并的数据
# cut_xtoy_usual/high：断面x到断面y的DataFrame数据（平峰/高峰）
cut_1to4_usual = pd.DataFrame(columns=['ID', 'TYPE', 'ENERGY_TYPE', 'SOURCE', 'TIME_DELTA', 'SPEED'])
cut_1to6_usual = pd.DataFrame(columns=['ID', 'TYPE', 'ENERGY_TYPE', 'SOURCE', 'TIME_DELTA', 'SPEED'])
cut_1to8_usual = pd.DataFrame(columns=['ID', 'TYPE', 'ENERGY_TYPE', 'SOURCE', 'TIME_DELTA', 'SPEED'])
cut_1to4_high = pd.DataFrame(columns=['ID', 'TYPE', 'ENERGY_TYPE', 'SOURCE', 'TIME_DELTA', 'SPEED'])
cut_1to6_high = pd.DataFrame(columns=['ID', 'TYPE', 'ENERGY_TYPE', 'SOURCE', 'TIME_DELTA', 'SPEED'])
cut_1to8_high = pd.DataFrame(columns=['ID', 'TYPE', 'ENERGY_TYPE', 'SOURCE', 'TIME_DELTA', 'SPEED'])


for i in range(len(cut1_usual)):  # 遍历进出口断面，进行匹配
    for j in range(len(cut4_usual)):
        if match(cut1_usual.loc[i, 'ID'], cut4_usual.loc[j, 'ID']) == 1 and (3.6*420/(cut4_usual.loc[j, 'TIME'] - cut1_usual.loc[i, 'TIME']))>0: # 舍去负值
            cut_1to4_usual.loc[len(cut_1to4_usual)] = [cut1_usual.loc[i, 'ID'], cut1_usual.loc[i, 'TYPE'],
                                                       cut1_usual.loc[i, 'ENERGY_TYPE'], cut1_usual.loc[i, 'SOURCE'],
                                                       cut4_usual.loc[j, 'TIME'] - cut1_usual.loc[i, 'TIME'],
                                                       3.6 * 420 / (cut4_usual.loc[j, 'TIME'] - cut1_usual.loc[i, 'TIME'])]
            break
# speed_avg_x_y_usual/high：x进口向y方向（eg.left左转/straight直行/right右转）的平均行程车速（平峰/高峰）
speed_avg_north_left_usual = cut_1to4_usual['SPEED'].mean()
print(cut_1to4_usual)
print('平峰时北进口左转的平均行程车速为：%.2fkm/h' % speed_avg_north_left_usual)


for i in range(len(cut1_usual)):  # 遍历进出口断面，进行匹配
    for j in range(len(cut6_usual)):
        if match(cut1_usual.loc[i, 'ID'], cut6_usual.loc[j, 'ID']) == 1 and (3.6*550/(cut6_usual.loc[j, 'TIME'] - cut1_usual.loc[i, 'TIME']))>0: # 舍去负值
            cut_1to6_usual.loc[len(cut_1to6_usual)] = [cut1_usual.loc[i, 'ID'], cut1_usual.loc[i, 'TYPE'],
                                                       cut1_usual.loc[i, 'ENERGY_TYPE'], cut1_usual.loc[i, 'SOURCE'],
                                                       cut6_usual.loc[j, 'TIME'] - cut1_usual.loc[i, 'TIME'],
                                                       3.6 * 550 / (cut6_usual.loc[j, 'TIME'] - cut1_usual.loc[i, 'TIME'])]
            break
speed_avg_north_straight_usual = cut_1to6_usual['SPEED'].mean()
print(cut_1to6_usual)
print('平峰时北进口直行的平均行程车速为：%.2fkm/h' % speed_avg_north_straight_usual)
cut_1to6_usual.to_excel("cut_1to6_usual.xlsx")



for i in range(len(cut1_usual)):  # 遍历进出口断面，进行匹配
    for j in range(len(cut8_usual)):
        if match(cut1_usual.loc[i, 'ID'], cut8_usual.loc[j, 'ID']) == 1 and (3.6*380/(cut8_usual.loc[j, 'TIME'] - cut1_usual.loc[i, 'TIME']))>0: # 舍去负值
            cut_1to8_usual.loc[len(cut_1to8_usual)] = [cut1_usual.loc[i, 'ID'], cut1_usual.loc[i, 'TYPE'],
                                                       cut1_usual.loc[i, 'ENERGY_TYPE'], cut1_usual.loc[i, 'SOURCE'],
                                                       cut8_usual.loc[j, 'TIME'] - cut8_usual.loc[i, 'TIME'],
                                                       3.6 * 380 / (cut8_usual.loc[j, 'TIME'] - cut1_usual.loc[i, 'TIME'])]
            break
print(cut_1to8_usual)
cut_1to8_usual.to_excel("cut_1to8_usual.xlsx")



# 高峰
for i in range(len(cut1_high)):  # 遍历进出口断面，进行匹配
    for j in range(len(cut4_high)):
        if match(cut1_high.loc[i, 'ID'], cut4_high.loc[j, 'ID']) == 1 and (3.6*420/(cut4_high.loc[j, 'TIME'] - cut1_high.loc[i, 'TIME']))>0: # 舍去负值
            cut_1to4_high.loc[len(cut_1to4_high)] = [cut1_high.loc[i, 'ID'], cut1_high.loc[i, 'TYPE'],
                                                       cut1_high.loc[i, 'ENERGY_TYPE'], cut1_high.loc[i, 'SOURCE'],
                                                       cut4_high.loc[j, 'TIME'] - cut1_high.loc[i, 'TIME'],
                                                       3.6 * 420 / (cut4_high.loc[j, 'TIME'] - cut1_high.loc[i, 'TIME'])]
            break
speed_avg_north_left_high = cut_1to4_high['SPEED'].mean()
print(cut_1to4_high)
print('高峰时北进口左转的平均行程车速为：%.2fkm/h' % speed_avg_north_left_high)
cut_1to4_high.to_excel("cut_1to4_high.xlsx")



for i in range(len(cut1_high)):  # 遍历进出口断面，进行匹配
    for j in range(len(cut6_high)):
        if match(cut1_high.loc[i, 'ID'], cut6_high.loc[j, 'ID']) == 1 and (3.6*550/(cut6_high.loc[j, 'TIME'] - cut1_high.loc[i, 'TIME']))>0: # 舍去负值
            cut_1to6_high.loc[len(cut_1to6_high)] = [cut1_high.loc[i, 'ID'], cut1_high.loc[i, 'TYPE'],
                                                       cut1_high.loc[i, 'ENERGY_TYPE'], cut1_high.loc[i, 'SOURCE'],
                                                       cut6_high.loc[j, 'TIME'] - cut1_high.loc[i, 'TIME'],
                                                       3.6 * 550 / (cut6_high.loc[j, 'TIME'] - cut1_high.loc[i, 'TIME'])]
            break
speed_avg_north_straigh_high = cut_1to6_high['SPEED'].mean()
print(cut_1to6_high)
print('高峰时北进口直行的平均行程车速为：%.2fkm/h' % speed_avg_north_straigh_high)
cut_1to6_high.to_excel("cut_1to6_high.xlsx")



for i in range(len(cut1_high)):  # 遍历进出口断面，进行匹配
    for j in range(len(cut8_high)):
        if match(cut1_high.loc[i, 'ID'], cut8_high.loc[j, 'ID']) == 1 and (3.6*380/(cut8_high.loc[j, 'TIME'] - cut1_high.loc[i, 'TIME']))>0: # 舍去负值
            cut_1to8_high.loc[len(cut_1to8_high)] = [cut1_high.loc[i, 'ID'], cut1_high.loc[i, 'TYPE'],
                                                       cut1_high.loc[i, 'ENERGY_TYPE'], cut1_high.loc[i, 'SOURCE'],
                                                       cut8_high.loc[j, 'TIME'] - cut1_high.loc[i, 'TIME'],
                                                       3.6 * 380 / (cut8_high.loc[j, 'TIME'] - cut1_high.loc[i, 'TIME'])]
            break
speed_avg_north_right_high = cut_1to8_high['SPEED'].mean()
print(cut_1to8_high)
print('高峰时北进口右转的平均行程车速为：%.2fkm/h' % speed_avg_north_right_high)
cut_1to8_high.to_excel("cut_1to8_high.xlsx")



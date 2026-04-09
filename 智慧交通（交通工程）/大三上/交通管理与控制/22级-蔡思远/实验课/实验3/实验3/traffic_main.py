from traffic_sign_timing import *
from traffic_default_parameter_info import *
from utils import *

def main():

    C = C_
    Y = 0
    iteration = 6 # 迭代次数
    gmin_flag = False
    # 四个方向的参量存放
    # 顺序为 [西, 东, 北, 南]
    direction_num = 4

    # 计算饱和流量
    S = [0 for _ in range(direction_num)]
    qd = [0 for _ in range(direction_num)]
    y = [0 for _ in range(direction_num)]
    # 这个字典只用于四个方向
    verse_channel_dict = {0 : 1, 1 : 0, 2 : 3, 3 : 2}

    # 开始迭代
    print('\n---------------------- 开始迭代 ----------------------')
    for iter in range(iteration):
        print(f'\n-------------------- 迭代{iter}次 --------------------')
        for i in range(direction_num):
            print(f'\n------------------- {direction[i]} -------------------')
            S[i], qd[i], y[i] = Cal_factor(channel[i], channel[verse_channel_dict[i]],hv[i],
                                           q[i], q[verse_channel_dict[i]], B[i],
                                           betal[i], betals[i], C, Ls, gel_list[i], geR_list[i],
                                           lamdal_list[i], lamdar_list[i], w[i])

        ## 计算信号配时

        # 计算相位最大流量比
        Y_max = []
        y_list = [0 for _ in range(direction_num)]
        tmp_list = []
        for scheme in phase:
            for i in range(direction_num):
                y_list[i] = FindchannelY(scheme[i], channel[i], y[i])
                tmp_list += y_list[i]
            y_max = max(tmp_list)
            Y_max.append(y_max)

        print(f'每个相位的最大流量比Ymax = {Y_max}')

        # 计算最大流量比总和
        Y = sum(Y_max)
        print(Y)
        print(f'最大流量比总和: {Y}')

        # if Y > 0.9, 需要重新设计
        if Y > 0.9:
            print('\n还没换方案-ERROR: Y > 0.9, 进口道车道划分不合理or周期时间太短, 需要重新设计!')
        
            # 输入新的渠化方案
            '''新的渠化方案 纯粹的测试'''
            channel[0] = ['S', 'L', 'SR']
            channel[1] = ['S', 'L', 'SR']
            channel[2] = ['S','S', 'L', 'SR']
            channel[3] = ['S', 'S', 'L', 'SR']

            q[0] = [250, 104, 113]
            q[1] = [416, 101, 80]
            q[2] = [1000, 660, 64, 113]
            q[3] = [1000, 757, 73, 120]
            continue
        else:
            print('\n------------------- 开始参数配时 -------------------')

            # 计算总损失时间
            L = Ls * num
            print(f'总损失时间: {L}')

            # 计算信号周期时长
            if gmin_flag == False:
                C = L / (1 - Y)
            else:
                C = 60
            print(f'验算/选取周期C: {C}')

            # 计算总有效绿灯时间
            Ge = C - L
            print(f'总有效绿灯时间Ge: {Ge}')

            # 计算相位有效绿灯时间
            ge_j = [(Ge * x) / Y for x in Y_max]
            print(f'有效相位绿灯时间ge_j: {ge_j}')

            # 计算各相位的绿信比
            lamda_j = [x / C for x in ge_j]
            print(f'绿信比lambda: {lamda_j}')

            # 计算各相位显示绿灯时间
            g_j = [(x - A + Ls) for x in ge_j]
            print(f'显示绿灯时间g_j: {g_j}')

            # 计算最短绿灯时间
            gmin = [0 for _ in range(len(phase))]
            gmin[0] = None

            # 这里看起来只算了三个相位
            # 第二个相位用东西
            # 第三个相位用南北
            # 总之在这里不具有普遍性 没有什么普遍性的公式啊
            for i in range(1, len(phase)):
                if i % 2 == 0: # 南北
                    gmin[i] = 7 + Lp_north_south / vp - I
                else:
                    gmin[i] = 7 + Lp_west_east / vp - I
            print(f'最短绿灯时间gmin: {gmin}')

            for i in range(1, len(phase)):
                if gmin[i] > g_j[i]:
                    print('\nERROR:配时方案不满足最短绿灯时间, 应扩大周期时长重新配时')

                    C = 60
                    Ge = C - L
                    ge_j = [(Ge * x) / Y for x in Y_max]
                    lamda_j = [x / C for x in ge_j]
                    g_j = [(x - A + Ls) for x in ge_j]

                    # 一共只有四个方向的进口道 
                    # 计算各进口道左转相位有效绿灯时长
                    # # ??????? # #
                    # gel = [g_j[0], g_j[0], g_j[2], g_j[2]]
                    # # 计算各进口道右转相位有效绿灯时长
                    # geR = [g_j[1], g_j[1], g_j[2], g_j[2]]


                    # lamdal = [lamda_j[0], lamda_j[0], lamda_j[2], lamda_j[2]]
                    # lamdar = [lamda_j[1], lamda_j[1], lamda_j[2], lamda_j[2]]

                    gmin_flag = True
                    continue





                    

            






if __name__ == "__main__":
    main()

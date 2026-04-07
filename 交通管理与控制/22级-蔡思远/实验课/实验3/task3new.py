import math

import numpy as np


def Width_factor(w): # w取3.2
    if 3.0 <= w <= 3.5:
        fw = 1
    elif 2.7 <= w < 3.0:
        fw = 0.4 * (w - 0.5)
    elif w > 3.5:
        fw = 0.05 * (w + 16.5)
    else:
        raise ValueError("车道宽度 w 不在定义的范围内")

    return fw


def Cart_factor(channel, hv, q, G):
    channel_hv = [0 for x in range(len(channel))]

    if 'SL' in channel:
        sum_q = [q[1]]
        if 'S' in channel:
            sum_q.append(q[0])
        if 'SR' in channel:
            sum_q.append(q[2])
        mean_q = np.mean(sum_q)
        l_q = mean_q-q[1]
        hv_q = l_q*hv
        sl_hv = hv_q/mean_q
        index = channel.index('SL')
        channel_hv[index] = sl_hv
    if 'SR' in channel:
        sum_q = [q[2]]
        if 'S' in channel:
            sum_q.append(q[0])
        if 'SL' in channel:
            sum_q.append(q[1])
        mean_q = np.mean(sum_q)
        r_q = mean_q - q[2]
        hv_q = r_q * hv
        sr_hv = hv_q / mean_q
        index = channel.index('SR')
        channel_hv[index] = sr_hv
    if 'S' in channel:
        index = extract(channel, 'S')
        for i in index:
            channel_hv[i] = hv

    channel_fg = [1 - (G + x) for x in channel_hv]
    print("(2)坡度及大车校正系数fg: ", channel_fg)
    return channel_fg


def extract(a, target):
    # 提取列表中某个元素的全部索引
    b = []
    for index, nums in enumerate(a):
        if nums == target:
            b.append(index)
    return b

def Bicycle_factor(B, betal, C, geL, phase, direction):
    import math

    bL = B*betal*(C-geL)/C
    import_road = ['west', 'east', 'north', 'south']
    index = import_road.index(direction)
    for i in range(len(phase)):
        direction_phase = phase[i][index]
        if direction_phase==[0,1,0]:
            fb = 1
            break
        else:
            fb = 1-(1+math.sqrt(bL))/geL
    print("(3)自行车影响校正系数fb: ", fb)
    print(" B: ", B)
    print(" β: ", betal)
    print(" ge: ", geL)
    print(" bL: ", bL)
    return fb


def TurnLeft_factor(channel, verse_channel, qt0, lambal, k):
    # # 检测当前进口道相位是否存在左转专用相位, 有的话, 对向直行车辆就不会对车流存在影响, 于是直接返回fL=1

    # 当前进口道没有左转专用道
    index_verse_S = verse_channel.index('S')
    # 对向车道数
    S_lane_sum = 0
    if 'S' in verse_channel:
        S_lane_sum += verse_channel.count('S')
    if 'SL' in verse_channel:
        S_lane_sum += verse_channel.count('SL')
    if 'SR' in verse_channel:
        S_lane_sum += verse_channel.count('SR')

    # 确定ξ(xi)
    if S_lane_sum == 1:
        xi = 1
    elif S_lane_sum == 2:
        xi = 0.625
    elif S_lane_sum == 3:
        xi = 0.51
    elif S_lane_sum == 4:
        xi = 0.44

    if 'L' in channel:
        fL = 1
    else:
        fL = math.exp(-0.001 * xi * (qt0 / lambal[k])) - 0.1

    print("(4)左转校正系数fL: ", fL)
    print(" ξ: ", xi)
    print(" qt0: ", qt0)
    print(" λ: ", lambal[k])

    return fL


def TurnRight_factor(channel, person, geR, lamdar,
                     C, Ls, bT):
    # # 检测是否存在右转专用道, 有的话就不会受到其他因素影响, 于是直接返回1
    # 判断是否有右转专用相位

    # 没有右转专用道
    # 确定行人影响校正系数
    fp_matrix_less_than_20 = {
        60: {0.4: 0.88, 0.5: 0.88, 0.6: 0.87},
        90: {0.4: 0.87, 0.5: 0.87, 0.6: 0.86},
        120: {0.4: 0.87, 0.5: 0.86, 0.6: 0.86}
    }

    fp_matrix_more_than_20 = {
        60: {0.4: 0.45, 0.5: 0.42, 0.6: 0.40},
        90: {0.4: 0.40, 0.5: 0.38, 0.6: 0.36},
        120: {0.4: 0.37, 0.5: 0.36, 0.6: 0.35}
    }

    # 四舍五入 geR / C 的值到 0.4, 0.5 或 0.6
    if geR/C < 0.45:
        rounded_geR_C = 0.4
    elif 0.45 <= geR/C < 0.55:
        rounded_geR_C = 0.5
    else:
        rounded_geR_C = 0.6

    # 检查周期 C 是否有效
    if C not in [60, 90, 120]:
        raise ValueError("周期 C 必须为 60, 90 或 120")

    # 根据 person 判断取哪个表格
    if person/(3600/C) < 20:
        fp = fp_matrix_less_than_20[C][rounded_geR_C]
    else:
        fp = fp_matrix_more_than_20[C][rounded_geR_C]

    # 计算直行自行车绿初驶出停车线所占用的时间
    '''
    红灯期
    到达排队自行车绿初驶出停车线的饱和流量,建议取 3600辆(m * h),
    自行车道宽度取 wb = 5m
    '''
    S_TS = 3600
    wb = 5
    tT = (3600 * (1 - lamdar) * bT) / (S_TS * wb)

    # 计算自行车影响校正系数fb_
    gj = geR - A + Ls
    fb_ = 1 - (tT / gj)

    # 计算fpb
    # 在fp和fb_中选最小的

    if 'R' in channel:
        fpb = 1
    else:
        fpb = min(fp, fb_)

    print("(5)右转校正系数fpb: ", fpb)
    print(" fp: ", fp)
    print(" λ: ", lamdar)
    print(" tT: ", tT)
    print(" fb: ", fb_)

    return fpb


def Saturation_flow(channel,q,fw,fg,fb,fL,fpb):
    SbT=1650
    SbL=1550
    SbR=1450
    channel_S=[0 for x in range(len(channel))]

    if 'S' in channel:
        index = extract(channel, 'S')
        ST = SbT * fw * fg[index[0]] * fb
        for i in index:
            channel_S[i] = ST

    if 'L' in channel:
        index = channel.index('L')
        SL = SbL * fw * fg[index] * fL
        channel_S[index] = SL

    if 'R' in channel:
        index = channel.index('R')
        SR = SbR * fw * fg[index] * fpb
        channel_S[index] = SR

    if 'SL' in channel:
        index = channel.index('SL')
        ST = SbT * fw * fg[index] * fb
        SL = SbL * fw * fg[index] * fL
        KL = ST / SL
        sum_q = [q[1]]
        if 'S' in channel:
            sum_q.append(q[0])
        if 'SR' in channel:
            sum_q.append(q[2])
        mean_q = np.mean(sum_q)
        qT = mean_q - q[1]
        qT1 = KL * q[1] + qT
        fTL = (qT + q[1]) / qT1
        STL = ST * fTL

        channel_S[index] = STL
        print("(6)直左车道校正系数fTL: ", fTL)
        print(" qT: ", qT)
        print(" qL: ", q[1])
        print(" SL': ", SL)
        print(" KL: ", KL)
        print(" qT': ", qT1)

    if 'SR' in channel:
        index = channel.index('SR')
        ST = SbT * fw * fg[index] * fb
        SR = SbR * fw * fg[index] * fpb
        kr=ST/SR
        sum_q = [q[2]]
        if 'S' in channel:
            sum_q.append(q[0])
        if 'SL' in channel:
            sum_q.append(q[1])
        mean_q = np.mean(sum_q)
        qT = mean_q - q[2]
        qT2 = kr * q[2] + qT
        fTR = (qT + q[2]) / qT2
        STR = ST * fTR
        channel_S[index] = STR
        print("(7)直右车道校正系数 fTR: ", fTR)
        print(" qT: ", qT)
        print(" qR: ", q[2])
        print(" SR': ", SR)
        print(" KR: ", kr)
        print(" qT': ", qT2)
    d = 0
    if channel.count('S') > 1:
        index = extract(channel, 'S')
        to = index[1]
        end = index[-1]+1
        del channel_S[to:end]
    channel_S = [round(x) for x in channel_S]
    print('\n饱和流量S: ', channel_S)
    return channel_S

def Diver_volume(channel,q):
    if channel.count('S')==1:
        if 'SR' in channel and 'SL' in channel:
            mean = np.mean(q)
            qd = [mean, mean, mean]
        elif 'SR' in channel and 'SL' not in channel:
            mean = (q[0] + q[2]) / 2
            qd = [mean, q[1], mean]
        elif 'SL' in channel and 'SR' not in channel:
            mean = (q[0] + q[1]) / 2
            qd = [mean, mean, q[2]]
        else:
            qd = q
    if channel.count('S')==2:
        if 'SR' in channel and 'SL' in channel:
            mean = np.sum(q)/4
            qd = [mean, mean, mean]
        elif 'SR' in channel and 'SL' not in channel:
            mean = (q[0] + q[2]) / 3
            qd = [mean, q[1], mean]
        elif 'SL' in channel and 'SR' not in channel:
            mean = (q[0] + q[1]) / 3
            qd = [mean, mean, q[2]]
        else:
            qd = q
    qd = [round(x) for x in qd]
    print("各车道的设计交通量qdmn: ", qd)
    return qd


def FindchannelY(scheme, channel, Y):
    ylist = []
    if 1 in scheme:
        index1 = extract(scheme, 1)
        if 0 in index1:
            if 'S' in channel:
                index2 = extract(channel, 'S')
                ylist.append(Y[index2[0]])
        if 1 in index1:
            if 'L' in channel:
                index3 = channel.index('L')
                ylist.append(Y[index3])
            if 'SL' in channel:
                index4 = channel.index('SL')
                if index4>2:
                    index4_adj = 2
                else:
                    index4_adj = index4
                ylist.append(Y[index4_adj])
        if 2 in index1:
            if 'R' in channel:
                index5 = channel.index('R')
                ylist.append(Y[index5])
            if 'SR' in channel:
                index6 = channel.index('SR')
                if index6>2:
                    index6_adj = 2
                else:
                    index6_adj = index6
                ylist.append(Y[index6_adj])
    return ylist


def Cal_factor(channel, verse_channel, hv, q, verse_q, B, betal, betas, phase, C,
               Ls, geL, geR, lamdaL, lamdaR, direction):
    # 1.车道宽度校正系数
    fw = Width_factor(direction)
    # 2.坡度及大车校正系数
    fg = Cart_factor(channel, hv, q, direction)
    # 3.直行车道的自行车影响校正系数
    fb = Bicycle_factor(B, betal, C, geL, phase, direction)
    # 4.左转校正系数
    fL = TurnLeft_factor(verse_channel, verse_q[0], lamdaL, phase, direction)
    # 5.右转校正系数
    person = 600 # 估计各向行人流量，人/h
    # 注意：教材案例北进口道右转校正系数取值为 fb，为勘误，实际上右转校正系数应取 min(fp, fb)
    fpb = TurnRight_factor(channel, person, geR, lamdaR, C, Ls, phase, betas*B, direction)
    # 饱和流量计算
    # 注意：教材案例 SbR 取值为 1550，为勘误。根据表 11-2，右转车道的基本饱和流量应取 1450
    S = Saturation_flow(channel, q, fw, fg, fb, fL, fpb, direction)
    # 计算各车道分流向的设计交通量 qd
    qd = Diver_volume(channel, q, direction)
    # 计算各车道分流向的流量比 y
    y = list(map(lambda x,y : x/y, qd, S))
    return S, qd, y

def Uniform_delay(x, lamda, C):

    d1 = 0.5 * C * ((1 - lamda) ** 2) / (1 - min(1, x) * lamda)
    return d1


def Random_delay(x, cap):

    import math

    T = 0.25  # Duration of the analysis phase, typically 0.25h
    e = 0.5   # Adjustment factor for intersection traffic signal control, typically 0.5

    d2 = 900 * T * ((x - 1) + math.sqrt((x - 1) ** 2 + 8 * e * x / (cap * T)))
    return d2



# 信号配时计算（主程序-迭代）
if __name__ == '__main__':
    # 输入各进口道的大车率
    west_hv = [0.04,0,0]
    east_hv = [0.04,0,0]
    north_hv = [0.02,0,0]
    south_hv = [0.02,0,0]
    # 输入各进口道的自行车平均流率，单位: 辆/min
    west_b = 28
    east_b = 30
    north_b = 20
    south_b = 27
    # 输入各进口道的自行车左转率
    west_betal_left = 0.1
    east_betal_left = 0.1
    north_betal_left = 0.25
    south_betal_left = 0.1
    # 输入各进口道的自行车直行率；
    ### ???算错：左转0.1/o.25，右转统一0.25，直行不应该是0.65/0.5吗
    west_betal_str = 0.65
    east_betal_str = 0.65
    north_betal_str = 0.5
    south_betal_str = 0.65
    # 输入交叉口各流向流量 q，按照直左右的顺序输入，例如 west_q = [513, 104, 113]
    west_q=[513,104,113]
    east_q = [416,101,80]
    north_q = [660,64,113]
    south_q = [757,73,120]
    # 输入渠化方案(S:直行 SL:直左 SR:直右 L:左转专用 R:右转专用)
    west_channel = ['S', 'L', 'SR']
    east_channel = ['S', 'L', 'SR']
    north_channel = ['S', 'SL', 'SR']
    south_channel = ['S', 'L', 'SR']

    #输入交叉口基本参数信息
    C=60
    I=3
    A=3
    num=3
    Ls = 3+I-A
    gel = (C - Ls * num) / num
    gel = [gel, gel, gel, gel]
    lamdal = (C - Ls * num) / (num * C)
    lamdal_list = [lamdal, lamdal, lamdal, lamdal]
    ger = (C - Ls * num) / num
    lamdar = (C - Ls * num)/(num * C)
    lamdar_list = [lamdar, lamdar, lamdar, lamdar]
    ger = [ger, ger, ger, ger]
    phase= [[[0, 1, 0], [0, 1, 0], [0, 0, 0], [0, 0, 0]],
            [[1, 0, 1], [1, 0, 1], [0, 0, 0], [0, 0, 0]],
            [[0, 0, 0], [0, 0, 0], [1, 1, 1], [1, 1, 1]]]
    # 人行道
    Lp_west_east = 17  # 东西向半幅人行横道长度
    Lp_north_south = 14  # 南北向半幅人行横道长度
    vp = 1  # 行人过街速度

    # 输出，循环试算

    w = 3.2
    Y = 0
    iteration = 6
    gmin_flag = False
    for z in range(iteration):
        print("\n\n#################### 第", z+1, "次试算 ####################")
        print("\n******************************* west *******************************")
        fw = Width_factor(w)
        print("(1)车道宽度校正系数fw：", fw)

        G = 0
        fg = Cart_factor(west_channel, west_hv[0], west_q, G)  ###

        fb = Bicycle_factor(west_b, west_betal_left, C, gel[0], phase, 'west')  ###

        fL = TurnLeft_factor(west_channel, east_channel, east_q[0], lamdal_list, 0)  ###

        person = 600
        fpb = TurnRight_factor(west_channel, person, ger[0], lamdar_list[0], C, Ls,
                               (west_betal_str * west_b))  ###

        west_S = Saturation_flow(west_channel, west_q, fw, fg, fb, fL, fpb)  ###

        west_qd = Diver_volume(west_channel, west_q)  ###

        west_y = list(map(lambda x, y: x / y, west_qd, west_S))

        print("\n******************************* east *******************************")
        fw = Width_factor(w)
        print("(1)车道宽度校正系数fw：", fw)

        G = 0
        fg = Cart_factor(east_channel, east_hv[0], east_q, G)  ###

        fb = Bicycle_factor(east_b, east_betal_left, C, gel[1], phase, 'east')  ###

        fL = TurnLeft_factor(east_channel, west_channel, west_q[0], lamdal_list, 1)  ###

        person = 600
        fpb = TurnRight_factor(east_channel, person, ger[1], lamdar_list[1], C, Ls,
                               (east_betal_str * east_b))  ###

        east_S = Saturation_flow(east_channel, east_q, fw, fg, fb, fL, fpb)  ###

        east_qd = Diver_volume(east_channel, east_q)  ###

        east_y = list(map(lambda x, y: x / y, east_qd, east_S))

        print("\n******************************* north *******************************")
        fw = Width_factor(w)
        print("(1)车道宽度校正系数fw：", fw)

        G = 0
        fg = Cart_factor(north_channel, north_hv[0], north_q, G)  ###

        fb = Bicycle_factor(north_b, north_betal_left, C, gel[2], phase, 'north')  ###

        fL = TurnLeft_factor(north_channel, south_channel, south_q[0], lamdal_list, 2)  ###

        person = 600
        fpb = TurnRight_factor(north_channel, person, ger[2], lamdar_list[2], C, Ls,
                               (north_betal_str * north_b))  ###

        north_S = Saturation_flow(north_channel, north_q, fw, fg, fb, fL, fpb)  ###

        north_qd = Diver_volume(north_channel, north_q)  ###

        north_y = list(map(lambda x, y: x / y, north_qd, north_S))

        print("\n******************************* south *******************************")
        fw = Width_factor(w)
        print("(1)车道宽度校正系数fw：", fw)

        G = 0
        fg = Cart_factor(south_channel, south_hv[0], south_q, G)  ###

        fb = Bicycle_factor(south_b, south_betal_left, C, gel[3], phase, 'south')  ###

        fL = TurnLeft_factor(south_channel, north_channel, north_q[0], lamdal_list, 3)  ###

        person = 600
        fpb = TurnRight_factor(south_channel, person, ger[3], lamdar_list[3], C, Ls,
                               (south_betal_str * south_b))  ###

        south_S = Saturation_flow(south_channel, south_q, fw, fg, fb, fL, fpb)  ###

        south_qd = Diver_volume(south_channel, south_q)  ###

        south_y = list(map(lambda x, y: x / y, south_qd, south_S))

        Y_max = []
        for scheme in phase:
            west_ylist = FindchannelY(scheme[0], west_channel, west_y)
            east_ylist = FindchannelY(scheme[1], east_channel, east_y)
            north_ylist = FindchannelY(scheme[2], north_channel,north_y)
            south_ylist = FindchannelY(scheme[3], south_channel, south_y)
            # print("west_ylist:",west_ylist)
            ymax = max(west_ylist + east_ylist + north_ylist + south_ylist)
            Y_max.append(ymax)
        print("相位最大流量比Ymax:", Y_max)
        Y = sum(Y_max)
        print("最大流量比总和Y:", Y)
        if Y > 0.9:
            print("\nError: Y> 0.9，进口车道划分不合理或周期时间太短需重新设计！")
            # 输入新的进口道渠化方案
            west_channel = ['S', 'L', 'SR']
            east_channel = ['S', 'L', 'SR']
            north_channel = ['S', 'S', 'L', 'SR']
            south_channel = ['S', 'S', 'L', 'SR']
            continue
        else:
            print("\n******************************* 配时参数 *******************************")
            # 计算总损失时间
            L = Ls * num
            print("总损失时间\n","L: ", L)
            # 计算信号周期时长
            if gmin_flag == False:
                C = L / (1 - Y)
            else:
                C = 60
            print("验算/选取周期\n", "C: ", C)
            # 计算总有效绿灯时间
            Ge = C - L
            print("总有效绿灯时间\n", "Ge: ",  Ge)
            # 计算相位有效绿灯时间
            ge_j = [Ge * x / Y for x in Y_max]
            print("有效绿灯时间\n","ge_j: ",  ge_j)
            # 计算各相位的绿信比
            lamda_j = [x / C for x in ge_j]
            print("绿信比\n","λj: ", lamda_j)
            # 计算各相位显示绿灯时间
            g_j = [x - A + Ls for x in ge_j]
            print("显示绿灯时间\n","gj: ", g_j)
            # 计算最短绿灯时间
            Lp_we = 17 # 东西向半幅人行横道长度取17m，采用路中央设置行人过街安全岛的方法
            Lp_ns = 14 # 南北向半幅人行横道长度取14m
            vp = 1  # 行人过街速度取1m/s
            gmin_phase2 = 7 + Lp_we / vp - I
            gmin_phase3 = 7 + Lp_ns / vp - I
            gmin = [None, gmin_phase2, gmin_phase3]
            print("最短绿灯时间\n","gmin: ", gmin)
            if gmin[1] > g_j[1] or gmin[2] > g_j[2]:
                print("\nError: 配时方案不满足最短绿灯时间，应该扩大周期时长重新计算！")

                # 按照最短绿灯时间要求，重新计算信号配时参数
                C = 60
                Ge = C - L

                ge_j = [Ge * x / Y for x in Y_max]
                lamda_j = [x / C for x in ge_j]
                g_j = [x - A + Ls for x in ge_j]

                gel = [g_j[0], g_j[0], g_j[2], g_j[2]]  # 计算各进口道的左转相位有效绿灯时长
                ger = [g_j[1], g_j[1], g_j[2], g_j[2]]  # 计算各进口道的右转相位有效绿灯时长

                lamdal = [lamda_j[0], lamda_j[0], lamda_j[2], lamda_j[2]]  # 左转车道的绿信比
                lamdar = [lamda_j[1], lamda_j[1], lamda_j[2], lamda_j[2]]  # 右转车道的绿信比

                gmin_flag = True
                continue
            else:
                print("\n******************************* 通行能力与饱和度 *******************************")
                # 通行能力
                print("各车道通行能力")
                west_cap = [west_S[0] * lamda_j[1], west_S[1] * lamda_j[0], west_S[2] * lamda_j[1]]
                west_cap = [round(x) for x in west_cap]
                east_cap = [east_S[0] * lamda_j[1], east_S[1] * lamda_j[0], east_S[2] * lamda_j[1]]
                east_cap = [round(x) for x in east_cap]
                north_cap = [north_S[0] * lamda_j[2], north_S[1] * lamda_j[0], north_S[2] * lamda_j[2]]
                north_cap = [round(x) for x in north_cap]
                south_cap = [south_S[0] * lamda_j[2], south_S[1] * lamda_j[2], south_S[2] * lamda_j[2]]
                south_cap = [round(x) for x in south_cap]

                print("west cap: ", west_cap)
                print("east cap: ", east_cap)
                print("north cap: ", north_cap)
                print("south cap: ", south_cap)

                # Calculate saturation for each lane
                print("各车道饱和度")

                west_x = list(map(lambda x, y: x / y, west_qd, west_cap))
                east_x = list(map(lambda x, y: x / y, east_qd, east_cap))
                north_x = list(map(lambda x, y: x / y, north_qd, north_cap))
                south_x = list(map(lambda x, y: x / y, south_qd, south_cap))

                print("west x: ", west_x)
                print("east x: ", east_x)
                print("north x: ", north_x)
                print("south x: ", south_x)

                print("\n******************************* 服务水平评估 *******************************")

                # Average delay
                print("(1) 车道均匀延误")

                west_d1 = [
                    Uniform_delay(west_x[0], lamda_j[1], C),
                    Uniform_delay(west_x[1], lamda_j[0], C),
                    Uniform_delay(west_x[2], lamda_j[1], C),
                ]

                east_d1 = [
                    Uniform_delay(east_x[0], lamda_j[1], C),
                    Uniform_delay(east_x[1], lamda_j[0], C),
                    Uniform_delay(east_x[2], lamda_j[1], C),
                ]

                north_d1 = [
                    Uniform_delay(north_x[0], lamda_j[2], C),
                    Uniform_delay(north_x[1], lamda_j[2], C),
                    Uniform_delay(north_x[2], lamda_j[2], C),
                ]

                south_d1 = [
                    Uniform_delay(south_x[0], lamda_j[2], C),
                    Uniform_delay(south_x[1], lamda_j[2], C),
                    Uniform_delay(south_x[2], lamda_j[2], C),
                ]

                print("west d1: ", west_d1)
                print("east d1: ", east_d1)
                print("north d1: ", north_d1)
                print("south d1: ", south_d1)

                # 随机延误
                print("(2) 车道随机延误")

                west_d2 = [
                    Random_delay(west_x[0], west_cap[0]),
                    Random_delay(west_x[1], west_cap[1]),
                    Random_delay(west_x[2], west_cap[2]),
                ]

                east_d2 = [
                    Random_delay(east_x[0], east_cap[0]),
                    Random_delay(east_x[1], east_cap[1]),
                    Random_delay(east_x[2], east_cap[2]),
                ]

                north_d2 = [
                    Random_delay(north_x[0], north_cap[0]),
                    Random_delay(north_x[1], north_cap[1]),
                    Random_delay(north_x[2], north_cap[2]),
                ]

                south_d2 = [
                    Random_delay(south_x[0], south_cap[0]),
                    Random_delay(south_x[1], south_cap[1]),
                    Random_delay(south_x[2], south_cap[2]),
                ]

                print("west d2: ", west_d2)
                print("east d2: ", east_d2)
                print("north d2: ", north_d2)
                print("south d2: ", south_d2)

                # 车道信号延误
                print("(3) 车道信号延误")

                west_d = list(map(lambda x, y: x + y, west_d1, west_d2))
                east_d = list(map(lambda x, y: x + y, east_d1, east_d2))
                north_d = list(map(lambda x, y: x + y, north_d1, north_d2))
                south_d = list(map(lambda x, y: x + y, south_d1, south_d2))

                print("west d: ", west_d)
                print("east d: ", east_d)
                print("north d: ", north_d)
                print("south d: ", south_d)

                # 进口道平均信号延误
                print("(4) 进口道平均信号延误")

                west_da = sum(list(map(lambda x, y: x * y / 4, west_d, west_qd))) / (sum(west_qd) / 4)
                east_da = sum(list(map(lambda x, y: x * y / 4, east_d, east_qd))) / (sum(east_qd) / 4)
                north_da = sum(list(map(lambda x, y: x * y / 4, north_d, north_qd))) / (sum(north_qd) / 4)
                south_da = sum(list(map(lambda x, y: x * y / 4, south_d, south_qd))) / (sum(south_qd) / 4)

                print("west dA: ", west_da)
                print("east dA: ", east_da)
                print("north dA: ", north_da)
                print("south dA: ", south_da)

                # 交叉口平均信号延误
                print("(5) 交叉口平均信号延误")

                # 每个方向的平均延误列表
                dA = [west_da, east_da, north_da, south_da]

                # 每个方向的车道流量总和
                qA = [sum(west_q), sum(east_q), sum(north_q), sum(south_q)]

                # 计算交叉口的平均信号延误
                dl = sum(list(map(lambda x, y: x * y / 4, dA, qA))) / (sum(qA) / 4)

                print("dl: ", dl)
                break


















import numpy as np
import math
from traffic_default_parameter_info import *
from utils import *

# 定义车道宽度校正系数 fw
def Width_factor(w=3.2):
    if w >= 3 and w <= 3.5:
        fw = 1
    elif w >= 2.7 and w < 3:
        fw = 0.4 * (w - 0.5)
    elif w > 3.5:
        fw = 0.005 * (w + 16.5)
    return fw

# 定义坡度and大车校正系数fg
'''
    # input:
        channel - 进口道渠化方案 例如: channel = ['S', 'L', 'SR']
        hv - 直行车大车率
        q - 进口道各流向设计交通量,例如q=[513, 104, 113],分别代表直
        行、左转、右转交通量
        G - 道路坡度,默认为0
    # return:
        channel_fg - 进口道各车道的大车校正系数
'''
# def Cart_factor(channel, hv, q, G=0):
def Cart_factor(channel, hv, q, G=0):
    channel_hv = [0 for _ in range(len(channel))]

    if 'SL' in channel:
        index_SL = channel.index('SL')
        sum_q = [q[index_SL]]

        if 'S' in channel:
            index_S = duplicate_value_all_index_in_list('S', channel)
            for i in index_S:
                sum_q.append(q[i])
        if 'SR' in channel:
            index_SR = channel.index('SR')
            sum_q.append(q[index_SR])

        mean_q = np.mean(sum_q)
        l_q = mean_q-q[index_SL]
        hv_q = l_q*hv
        sl_hv = hv_q/mean_q
        channel_hv[index_SL] = sl_hv
    if 'SR' in channel:
        index_SR = channel.index('SR')
        sum_q = [q[index_SR]]
        if 'S' in channel:
            index_S = duplicate_value_all_index_in_list('S', channel)
            for i in index_S:
                sum_q.append(q[i])
        if 'SL' in channel:
            index_SL = channel.index('SL')
            sum_q.append(q[index_SL])
        mean_q = np.mean(sum_q)
        r_q = mean_q-q[index_SR]
        hv_q = r_q*hv
        sr_hv = hv_q/mean_q
        index = channel.index('SR')
        channel_hv[index] = sr_hv
    if 'S' in channel:
        index = extract(channel, 'S') # 用到extract自定义函数
        for i in index:
            channel_hv[i] = hv
    
    # 理论公式计算
    channel_fg = [1-(G+x) for x in channel_hv]

    print(f'channel_fg:{channel_fg}')
    # print("坡度及大车校正系数fg: ", channel_fg)
    return channel_fg

def extract(a, target):
    # 提取列表中某个元素的全部索引
    b = []
    for index, nums, in enumerate(a):
        if(nums == target):
            b.append(index)
    return b

# 自定义自行车影响校正系数fb
'''
    # 函数名称:Bicycle_factor
    # 额外导入:math
    # 计算直行车道的自行车影响校正系数fb

    # input:
    B - 进口道的自行车流量
    betal - 进口道的自行车左转率
    C - 周期时长
    geL - 左转相位有效绿灯时长
    phase - 交叉口相位方案
    direction - 进口道方向

    # return:
    fb - 该方向进口道直行车道的自行车影响校正系数
'''
def Bicycle_factor(B_, betal, C, geL, channel):
    bL = B_ * betal * (C - geL) / C

    if 'L' in channel:
        fb = 1
    else:
        fb = 1 - (1 + math.sqrt(bL)) / geL
    
    # print("自行车影响校正系数fb: ", fb)
    # print("     B: ", B_)
    # print("     ß: ", betal)
    # print("     ge: ", geL)
    # print("     bL: ", bL)
    return fb

# 定义左转校正系数fL
'''
    # 函数名称:TurnLeft_factor
    # 计算左转专用车道的左转校正系数fL
    # input:
        channel - 对向进口道的渠化方案
        qt0 - 对向进口道的直行车流量,pcu/h
        lamdal - 左转车道的相位绿信比
        phase - 交叉口相位方案
        direction - 进口道方向
    # return:
        fL - 进口道左转专用车道的左转校正系数
'''
def TurnLeft_factor(channel, verse_channel, qt0, lambal):
    # # 检测当前进口道相位是否存在左转专用相位, 有的话, 对向直行车辆就不会对车流存在影响, 于是直接返回fL=1
    if 'L' in channel:
        fL = 1
        return fL
    
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
    
    fL = math.exp(-0.001 * xi * (qt0[index_verse_S] / lambal)) - 0.1
    return fL

# 定义右转校正系数fpb
'''
函数名称:TurnRight_factor
额外导入:numpy、math
# 计算右转专用车道的行人/自行车影响校正系数fpb
    # input:
        channel - 对向进口道的渠化方案
        person - 各向行人流量,人/h
        geR - 右转相位的有效绿灯时间
        lamdar - 右转相位的绿信比
        C - 周期时长
        Ls - 相位损失时间
        phase - 交叉口相位方案
        bT - 直行自行车每周期平均交通量,辆/周期
        direction - 进口道方向
    # return:
        fpb - 进口道右转专用车道的行人/自行车影响校正系数
'''
def TurnRight_factor(channel, person, geR, lamdar,
                     C, Ls, bT):
    # # 检测是否存在右转专用道, 有的话就不会受到其他因素影响, 于是直接返回1
    # 判断是否有右转专用相位
    if 'R' not in channel:
        fpb = 1
        return fpb

    # 没有右转专用道
    # 确定行人影响校正系数
    C_list = [60, 90, 120]
    geR_divided_by_C_list = [0.4, 0,5, 0.6]
    fp_matrix_less_than_20 = [0.88, 0.88, 0.87,
                              0.87, 0.87, 0.86,
                              0.87, 0.86, 0.86]
    fp_matrix_more_than_20 = [0.45, 0.42, 0.40,
                              0.40, 0.38, 0.36,
                              0.37, 0.36, 0.35]
    
    for i in range(len(C_list)):
        for j in range(len(geR_divided_by_C_list)):
            if C == C_list[i] and (geR / C) == geR_divided_by_C_list[j]:
                if person < 20:
                    fp = fp_matrix_less_than_20[i][j]
                else:
                    fp = fp_matrix_more_than_20[i][j]

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
    gj = geR - A - Ls
    fb_ = 1 - (tT / gj)

    # 计算fpb
    # 在fp和fb_中选最小的
    fpb = min(fp, fb_)
    return fpb

# 各车道饱和流量计算
'''
# 函数名称:Saturation_flow
# 额外导入:numpy
# 计算各车道的饱和流量
    # input:
        channel - 进口道渠化方案
        q - 进口道设计交通量
        fw - 车道宽度校正系数
        fg - 坡度及大车校正系数
        fb - 直行车道的自行车影响校正系数
        fL - 左转专用车道的左转校正系数
        fpb - 右转专用车道的行人/自行车影响校正系数
    # return:
        channel_S - 各车道的饱和流量
'''
def Saturation_flow(channel, q, fw, fg, fb, fL, fpb,
                    SbT=1650, SbL=1550, SbR=1450) -> list:
    
    print(channel)
    # 各车道的饱和流量(用于return)
    channel_S = [0 for _ in range(len(channel))]

    # 使用自定义的函数给列表去重, 并不改变原来顺序
    # 去重的目的是避免重复计算多条直行道'S'的值
    # channel = list_deduplicate(channel)

    # 以下是几个默认值
    # 直行车道的基本饱和流量pcu/h
    # SbT = 1650
    # 左转车道的基本饱和流量
    # SbL = 1550
    # 右转车道的基本饱和流量
    # SbR = 1450

    # 计算直行车饱和流量(如果存在直行)
    if 'S' in channel:
        print('in S')
        index_S = duplicate_value_all_index_in_list('S', channel)
        print(f'index_S:{index_S}')
        for i in index_S:
            ST = SbT * fw * fg[i] * fb
            print(f'SbT:{SbT}')
            print(f'fw:{fw}')
            print(f'fg[{i}]:{fg[i]}')
            print(f'fb:{fb}')
            channel_S[i] = ST
    # 计算左转专用车道饱和流量(如果存在左转专用道)
    if 'L' in channel:
        print('in L')
        index = channel.index('L')
        SL = SbL * fw * fg[index] * fL
        channel_S[index] = SL
    # 计算右转专用车道饱和流量(如果存在右转专用道)
    if 'R' in channel:
        print('in R')
        index = channel.index('R')
        SR = SbR * fw * fg[index] * fr * fpb
        channel_S[index] = SR
    # 计算直左车道的饱和流量(如果存在直左车道)
    if 'SL' in channel:
        print('in SL')
        index_SL = channel.index('SL')

        ST_ = SbT*fw*fg[index_SL]*fb
        # 有左转专用相位SL
        # 无左转专用相位SL_
        SL_ = SbL*fw*fg[index_SL]*fL
        KL = ST_/SL_

        sum_q = [q[index_SL]]
        if 'S' in channel:
            index_S = duplicate_value_all_index_in_list('S', channel)
            for i in index_S:
                sum_q.append(q[i])
        if 'SR' in channel:
            index_SR = channel.index('SR')
            sum_q.append(q[index_SR])
        mean_q = np.mean(sum_q)
        # 合用车道中直行车交通量qTL
        qTL = mean_q-q[index_SL]
        # 直左合用车道直行车当量qT1
        qT1 = KL*q[index_SL]+qTL
        fTL = (qTL+q[index_SL])/qT1
        STL = ST_*fTL

        channel_S[index_SL] = STL
    
    # 计算直右车道的饱和流量(如果存在直右车道)
    if 'SR' in channel:
        index_SR = channel.index('SR')
        
        ST_ = SbT * fw * fg[index_SR] * fb
        # 有右转专用相位SR
        # 无右转专用相位SR_
        SR_ = SbR * fw * fg[index_SR] * fr * fpb
        KR = ST_ / SR_
        
        # 计算qT
        sum_q = [q[index_SR]]
        if 'S' in channel:
            index_S = duplicate_value_all_index_in_list('S', channel)
            for i in index_S:
                sum_q.append(q[i])
        if 'SL' in channel:
            index_SL = channel.index('SL')
            sum_q.append(q[index_SL])
        mean_q = np.mean(sum_q)
        qTR = mean_q - q[index_SR]
        # 直右合用车直行车当量qT2
        qT2 = KR * q[index_SR] + qTR
        # 直右合流校正系数fTR
        fTR = (qTR + q[index_SR]) / qT2
        # 直右车道的饱和流量
        STR = ST_ * fTR

        channel_S[index_SR] = STR
    # 输出各车道饱和流量值
    print(f'channel_S: {channel_S}')
    return channel_S


# 进口道各车道设计交通量qdmn计算
'''
    # input:
        channel - 进口道渠化方案
        q - 进口道设计交通量

    # return:
        qd - 各车道的设计交通量
'''
# Dive volume 这个名字我完全不知道在这儿是啥意思, 只能说对着讲义先写着
def Diver_volume(channel, q) -> list:
    # 创建各车道的设计交通量列表qd
    qd = [0 for _ in range(len(channel))]

    # 如果channel为 直, 左直, 直右
    # qd等于三者流量均值
    if all(x in channel for x in ['S', 'SR', 'SL']):
        # qdmn -- qd mean (是个平均值)
        qdmn = np.mean(q)
        qd = [qdmn for _ in range(len(channel))]
    
    # 如果渠化方案是 直, 左, 直右, 则是含有直行车流的均值
    elif all(x in channel for x in ['S', 'L', 'SR']):
        # 获取直行道S在channel中的全部索引, 以便能够提取q中数值
        index_S = duplicate_value_all_index_in_list('S', channel)
        print(f'直, 左, 直右: {len(index_S)}')
        index_SR = channel.index('SR')
        index_L = channel.index('L')
        q_S_sum = 0
        for i in index_S:
            q_S_sum += q[i]
        qdmn = (q_S_sum + q[index_SR]) / (len(index_S) + 1)
        qd = [qdmn for _ in range(len(channel))]
        # 左转专用车道设计车流量不变
        qd[index_L] = q[index_L]
    
    # 如果渠化方案是 直, 直左, 右, 则是含有直行车流的均值
    elif all(x in channel for x in ['S', 'SL', 'R']):
        index_S = duplicate_value_all_index_in_list('S', channel)
        print(f'直, 直左, 右: {len(index_S)}')

        index_SL = channel.index('SL')
        index_R = channel.index('R')
        q_S_sum = 0
        for i in index_S:
            q_S_sum += q[i]
        qdmn = (q_S_sum + q[index_SL]) / (len(index_S) + 1)
        qd = [qdmn for _ in range(len(channel))]
        # 左转专用车道设计车流量不变
        qd[index_R] = q[index_R]
    
    # 不知道直左右是否需要单独拉出来讨论计算
    # elif 'SLR' in channel:

    # 如果渠化方案中不存在 直左, 直右, 直左右, 则所有车道qdmn保持原来不变
    else:
        qd = q
    
    # 返回qd
    return qd


# 查找每一个相位对应的各车道流量比
'''
# 函数名称:FindchannelY
# 寻找各相位下每个进口道有哪些车道允许通过并添加其车道流量比
    # input:
        scheme - 第i 相位某进口道的通行规则
        channel - 进口道的渠化方案
        Y - 进口道流量比
    #return:
        ylist - 对应相位下的允许通行车道流量比
'''
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

# 各车道饱和流量以及其校正系数赋值
'''
# 函数名称:Cal_factor
# 饱和流量及其校正系数赋值
    # input:
        channel - 进口道渠化方案
        verse_channel - 对向进口道的渠化方案
        hv - 进口道大车率
        q - 进口道设计交通量
        verse_q - 对向进口道的设计交通量
        B - 进口道的自行车流量
        betal - 进口道的自行车左转率
        betas - 进口道的自行车直行率
        phase - 交叉口相位方案
        C - 信号周期时长
        Ls - 相位损失时间
        geL - 左转相位有效绿灯时间
        geR - 右转相位有效绿灯时间
        lamdaL - 左转专用车道绿信比
        lamdaR - 右转专用车道相位绿信比
        direction - 进口道方向
    # return:
        S - 进口道各车道的饱和流量
        qd - 进口道各车道的设计交通量
        y - 进口道各车道的流量比
'''
def Cal_factor(channel, verse_channel, hv, q, verse_q, B_, betal, betas, C, Ls, geL, geR, lamdaL,
lamdaR, w):
    # 1.车道宽度校正系数
    fw = Width_factor(w)

    # 2.坡度及大车校正系数
    fg = Cart_factor(channel, hv, q)

    # 3.直行车道的自行车影响校正系数
    fb = Bicycle_factor(B_, betal, C, geL, channel)

    # 4.左转校正系数
    fL = TurnLeft_factor(channel, verse_channel, verse_q, lamdaL)

    # 5.右转校正系数
    person = 600 # 估计各向行人流量，人/h
    # 注意：教材案例北进口道右转校正系数取值为fb，为勘误，实际上右转校正系数应取min(fp, fb)

    fpb = TurnRight_factor(channel, person, geR, lamdaR, C, Ls, betas*B_)

    # 饱和流量计算
    # 注意：教材案例SbR 取值为1550，为勘误。根据表11-2，右转车道的基本饱和流量应取1450
    S = Saturation_flow(channel, q, fw, fg, fb, fL, fpb)

    # 计算各车道分流向的设计交通量qd
    qd = Diver_volume(channel, q)

    # 计算各车道分流向的流量比y
    y = list(map(lambda x,y : x/y, qd, S))

    return S, qd, y


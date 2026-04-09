import numpy as np


def Width_factor(w=3.2):
    if 3.0 <= w <= 3.5:
        fw = 1
    elif 2.7 <= w < 3.0:
        fw = 0.4 * (w - 0.5)
    elif w > 3.5:
        fw = 0.05 * (w + 16.5)
    else:
        raise ValueError("车道宽度 w 不在定义的范围内")

    return fw


def Cart_factor(channel, hv, q, director, G=0):
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


def TurnLeft_factor(channel, qt0, lamdal, phase, direction):

    # 表 3 对向直行车道的影响系数 ξ
    xi_values = {
        1: 1.0,
        2: 0.625,
        3: 0.51,
        4: 0.44
    }

    # 获取相位影响系数 ξ
    if phase in xi_values:
        xi = xi_values[phase]
    else:
        raise ValueError("相位方案不在预定义范围内")

    # 计算 λ = Gc / jc
    lamda = qt0 / lamdal

    # 根据公式 (6) 计算 fL
    fL = np.exp(-0.001 * xi * qt0 / lamda) - 0.1

    return fL


def TurnRight_factor(channel, person, geR, lamdar, C, Ls, phase, bT, direction):

    # 表 4 行人影响校正系数 fp
    fp_table = {
        (60, '<20'): [0.88, 0.88, 0.87],
        (60, '>20'): [0.45, 0.42, 0.40],
        (90, '<20'): [0.87, 0.87, 0.86],
        (90, '>20'): [0.40, 0.38, 0.36],
        (120, '<20'): [0.87, 0.86, 0.86],
        (120, '>20'): [0.37, 0.36, 0.35]
    }

    # 确定行人影响校正系数 fp
    category = '<20' if person < 20 else '>20'
    fp_values = fp_table.get((C, category))
    if not fp_values:
        raise ValueError("输入的周期时长 C 或行人流量类别超出范围")
    # 根据 geR/C 确定影响校正系数
    geR_ratio = geR / C
    if geR_ratio <= 0.4:
        fp = fp_values[0]
    elif geR_ratio <= 0.5:
        fp = fp_values[1]
    elif geR_ratio <= 0.6:
        fp = fp_values[2]

    # 计算自行车绿灯初期驶出时间 t_r
    Wb = 5  # 自行车车道宽度，单位 米
    Sts = 3600  # 自行车驶出速度，单位 辆/(m.h)
    tr = (3600 * (1 - lamdar) * bT) / (Sts * Wb)

    # 计算自行车影响校正系数 f'b
    fb_prime = 1 - (tr / geR)

    # 判断是否存在右转专用相位，若存在直接返回 fpb = 1
    if phase in channel:
        fpb = 1.0
    else:
        # 利用公式 (8) 计算 fpb
        fpb = min(fp, fb_prime)

    return fpb

def Saturation_flow(channel,q,fw,fg,fb,fL,fpb):
    SbT=1650
    SbL=1550
    SbR=1450
    channel_S=[]
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
        print("(6)直左车道校正系数 fTL: ", fTL)
        print(" qT: ", qT)
        print(" qL: ", q[1])
        print(" SL': ", SL)
        print(" KL: ", KL)
        print(" qT': ", qT1)

    if 'L' in channel:
        index = channel.index('L')
        SL = SbL * fw * fg[index] * fL
        channel_S[index] = SL
        print("左转专用车道饱和流量：",SL)

    if 'S' in channel:
        index = channel.index('S')
        ST = SbT * fw * fg[index] * fb
        channel_S[index] = ST
        print("直行车道饱和流量：",ST)

    if 'R' in channel:
        index = channel.index('R')
        SR = SbR * fw * fg[index] * fpb
        channel_S[index] = SR
        print("右转专用车车道饱和流量：",SR)

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
        qT1 = kr * q[2] + qT
        fTR = (qT + q[2]) / qT1
        STR = ST * fTR
        channel_S[index] = STR
        print("直右车道校正系数 fTR: ", fTR)
        print(" qT: ", qT)
        print(" qR: ", q[2])
        print(" SR': ", SR)
        print(" KR: ", kr)
        print(" qT': ", qT1)
    print("个车道饱和流量：",channel)
    return

def Diver_volume(channel,q):
    if channel==['SL','S','SR']:
        qd=[(q[0]+q[1]+q[2])/3,(q[0]+q[1]+q[2])/3,(q[0]+q[1]+q[2])/3]
    if channel==['L','S','SR']:
        qd=[q[0],(q[1]+q[2])/2,(q[1]+q[2])/2]
    if channel==['SL','S','R']:
        qd=[(q[1]+q[0])/2,(q[1]+q[0])/2,q[2]]
    if 'SL' not in channel:
        qd=q
    if 'SR' not in channel:
        qd=q
    if 'SLR' not in channel:
        qd=q
    print("进口道各车道设计交通量:",qd)
    return


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


# 信号配时计算（主程序-迭代）
if __name__ == '__main__':
    # 输入各进口道的大车率
    west_hv = [0.04,0,0]
    east_hv = [0.04,0,0]
    north_hv = [0.02,0,0]
    south_hv = [0.02,0,0]
    # 输入各进口道的自行车流量，单位: 辆/周期
    west_b = 1260
    east_b = 1350
    north_b = 900
    south_b = 1215
    # 输入各进口道的自行车左转率
    west_betal=0.25
    east_betal = 0.1
    north_betal = 0.1
    south_betal = 0.1
    # 输入各进口道的自行车直行率；
    west_betals=0.5
    east_betal = 0.65
    north_betal = 0.65
    south_betal = 0.65
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
    phase= [[[0, 1, 0], [0, 1, 0], [0, 0, 0], [0, 0, 0]],
            [[1, 0, 1], [1, 0, 1], [0, 0, 0], [0, 0, 0]],
            [[0, 0, 0], [0, 0, 0], [1, 1, 1], [1, 1, 1]]]








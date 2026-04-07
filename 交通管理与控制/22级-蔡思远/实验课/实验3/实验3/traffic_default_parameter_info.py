# 交叉口基本参数信息--全局默认变量
# 各进口道的大车率
west_hv: float = 0.04
east_hv: float = 0.04
north_hv: float = 0.02
south_hv: float = 0.02
hv: list = [west_hv, east_hv, north_hv, south_hv]

# 各进口道的自行车流量
west_B: int = 28
east_B: int = 30
north_B: int = 20
south_B: int = 27
B: list = [west_B, east_B, north_B, south_B]

# 各进口道的自行车左转率
west_betal: float = 0.10
east_betal: float = 0.10
north_betal: float = 0.25
south_betal: float = 0.10
betal: list = [west_betal, east_betal, north_betal, south_betal]

# 各进口道的自行车直行率
west_betals: float = 0.75
east_betals: float = 0.75
north_betals: float = 0.65
south_betals: float = 0.75
betals: list = [west_betals, east_betals, north_betals, south_betals]

# 各个进口道车道宽度
west_w: float = 3.2
east_w: float = 3.2
north_w: float = 3.2
south_w: float = 3.2
w: list = [west_w, east_w, north_w, south_w]

# 各进口道的渠化方案
west_channel: list = ['S', 'L', 'SR']
east_channel: list = ['S', 'L', 'SR']
north_channel: list = ['S', 'SL', 'SR']
south_channel: list = ['S', 'L', 'SR']
channel: list = [west_channel, east_channel, north_channel, south_channel]

# 交叉口各流向流量
# q = [直, 左, 右] 按理来讲应该和channel的顺序是一样的
# west_q: list = [513, 104, 113]
west_q: list = [250, 104, 113]
east_q: list = [416, 101, 80]
north_q: list = [660, 64, 113]
south_q: list = [757, 73, 120]
q = [west_q, east_q, north_q, south_q]

# 设置基本参数
C_ = 60 # 初始信号周期
I = 3  # 绿灯间隔时间
A = 3 # 黄灯时间
num = 3 # 相位数
Ls = 3 # 相位损失时间

# 相位方案
# [0, 0, 0] 直左右
# [[西],[东],[北],[南]] 
# scheme是其中的某一相位[0, 1, 0]
phase = [[[0, 1, 0], [0, 1, 0], [0, 0, 0], [0, 0, 0]],
         [[1, 0, 1], [1, 0, 1], [0, 0, 0], [0, 0, 0]],
         [[0, 0, 0], [0, 0, 0], [1, 1, 1], [1, 1, 1]]] 
# 方向
direction = ['west', 'east', 'north', 'south']

fr = 1 # 左右转弯半径校正系数

gel = (C_ - Ls * num) / num # 左转相位有效绿灯时长
# geR = (C_ - Ls * num) / num # 右转相位有效绿灯时间
geR = 24
lamdal = (C_ - Ls * num) / (num * C_) # 左转专用车道相位绿信比
lamdar = (C_ - Ls * num) / (num * C_) # 右转专用车道相位绿信比

# 各个进口道的左转相位有效绿灯时间
gel_list = [gel, gel, gel, gel]

# 各个进口道的右转相位有效绿灯时间
geR_list = [geR, geR, geR, geR]

# 各个进口道的左转专用车道相位绿信比
lamdal_list = [lamdal, lamdal, lamdal, lamdal]

# 各个进口道的右转专用侧道相位绿信比
lamdar_list = [lamdar, lamdar, lamdar, lamdar]

# 人行道
Lp_west_east = 17 # 东西向半幅人行横道长度
Lp_north_south = 14 # 南北向半幅人行横道长度
vp = 1 # 行人过街速度


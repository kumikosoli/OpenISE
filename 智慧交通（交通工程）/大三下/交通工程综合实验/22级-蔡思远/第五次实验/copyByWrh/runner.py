from __future__ import absolute_import
from __future__ import print_function

import os
import sys
import optparse
import numpy as np

if 'SUMO_HOME' in os.environ:
    tools = os.path.join(os.environ['SUMO_HOME'], 'tools')
    sys.path.append(tools)
else:
    sys.exit("please declare environment variable 'SUMO_HOME'")

from sumolib import checkBinary
import traci

def run():
    """execute the TraCI control loop"""
    step = 0  # 初始仿真时间

    while traci.simulation.getMinExpectedNumber() > 0:
        traci.simulationStep()  # 持续仿真
        # 等待切换位置编码号
        # 这一段，使用列表推导式和startswith方法，检查上一时间步的检测到的车辆ID号，是否有字符"EW"开头
        bus_num = any(word.startswith("EW") for word in traci.inductionLoop.getLastStepVehicleIDs("0"))
        # 如果bus_num > 0:
        # 根据上一时间步通过该检测器的车辆平均车长
        det_id_list = [str(i) for i in range(0, 6)]  # 检测器ID列表
        mean_length = []  # 每个检测器平均车长列表

        for i in det_id_list:
            l = traci.inductionloop.getLastStepMeanLength(i)  # 当前检测器在上一时间步的平均车长
            if l < 0:  # 如果上一个时间步无法无车，则返回-1
                l = 0
            mean_length.append(l)
        print(mean_length)
        if np.max(mean_length) > 10:  # 系统口下条件是上一时间步的车辆车长较长
            print(np.argmax(mean_length))

        # argmax 用于反查索引，要输出成符合编号的车辆ID
        v_id = traci.inductionloop.getLastStepVehicleIDs(str(np.argmax(mean_length)))[0]
        print(type(v_id))
        traci.trafficlight.setPhase("cluster_2473907747_273651802_2737637179_2737637287", 0)  # 将信号灯切换到直行方向
        traci.vehicle.highlight(vehID=v_id)  # 标记进出口道的公共汽车，便于易观察

        step += 1  # 仿真时间长度1
        traci.close()
        sys.stdout.flush()

def get_options():
    """SUMO 必须配置的文件"""
    optParser = optparse.OptionParser()
    optParser.add_option("--nogui", action="store_true", default=False, help="run the commandline version of sumo")
    options, args = optParser.parse_args()
    return options

if __name__ == "__main__":
    options = get_options()

    if options.nogui:
        sumoBinary = checkBinary('sumo')
    else:
        sumoBinary = checkBinary('sumo-gui')

    print(sumoBinary)

    # 使用traci接口的方式。Sumo作为进程启动，然后python脚本连接运行
    traci.start([sumoBinary, "-c", "data/GC_GQ.sumocfg", "--tripinfo-output", "tripinfo.xml"])  # 输出仿真信息
    # traci.gui.setSchema('View #0', 'Real World') # 真实世界视图（可换），如果不调用gui 需要注释掉
    traci.simulation.saveState('light_state.xml')  # 保存信号状态信息
    run()  # 进行感应式信号

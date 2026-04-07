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
    step = 0 
    while traci.simulation.getMinExpectedNumber() > 0:
        traci.simulationStep()
        det_id_list = [str(i) for i in range(0, 6)]
        mean_length = []
        j=0
        for i in det_id_list:
            l = traci.inductionloop.getLastStepMeanLength(i)
            if l < 0:
                l = 0
            elif l > 7:
                j += 1
            mean_length.append(l)
        print(mean_length)
        if  j > 1:
            v_id = traci.inductionloop.getLastStepVehicleIDs(str(np.argmax(mean_length)))[0]
            print(type(v_id))
            traci.trafficlight.setPhase("cluster_2473907747_2736518102_2737637179_2737637287",0)
            traci.vehicle.highlight(vehID=v_id)
        step += 1
    traci.close()
    sys.stdout.flush()

def get_options():
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
traci.start([sumoBinary, "-c", "data/GC_GQ.sumocfg", "--tripinfo-output", "tripinfo.xml"])
traci.simulation.saveState('1')
run()
import pulp
import pandas as pd
up = {}
up_bound1 ={}

variables = {}
for i in range(1,134):
    variables[f"x{i}_1"] = pulp.LpVariable(f'{up[i - 1]}_1_video_num', 0, 10, pulp.LpContinuous)

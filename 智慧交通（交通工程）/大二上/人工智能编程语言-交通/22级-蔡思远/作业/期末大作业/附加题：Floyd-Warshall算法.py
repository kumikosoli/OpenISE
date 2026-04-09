def read_txt_to_2d_list(file_path):
    result = []
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            result.append(line.strip().split())
    return result


set_nodes={"v0":0,"v1":1,"v2":2,"v3":3,"v4":4,"v5":5}

A = read_txt_to_2d_list('map.txt')
dis = [[float(x) for x in row] for row in A]

#i为中间节点
for i in range(len(set_nodes)):
    #j为起点
    for j in range(len(set_nodes)):
        #k为终点
        for k in range(len(set_nodes)):
            #更新最短距离
            dis[j][k]=min(dis[j][k], dis[j][i]+dis[i][k])
print("各点的之间的最短距离：示例：若矩阵[0][1]为inf，表示节点0到节点1没有路径：\n",dis)

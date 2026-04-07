import numpy as np
import  networkx as nx
import matplotlib.pyplot as plt
from matplotlib import font_manager


font_manager.fontManager.addfont('/Users/caisiyuan/anaconda3/lib/python3.11/site-packages/matplotlib/mpl-data/fonts/ttf/SimHei.ttf')
plt.rcParams['font.sans-serif']=['SimHei'] # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus']=False # 用来正常显示负号

def Dijkstra(G, start):
    start = start - 1
    inf = float('inf')
    node_num = len(G)
    # visited：哪些顶点加入过
    visited = [0] * node_num
    dis = {node: G[start][node] for node in range(node_num)}
    # parents：最终求出最短路径后，每个顶点的上一个顶点是谁
    parents = {node: -1 for node in range(node_num)}
    visited[start] = 1
    last_point = start

    for i in range(node_num - 1):
        min_dis = inf
        for j in range(node_num):
            if visited[j] == 0 and dis[j] < min_dis:
                min_dis = dis[j]
                last_point = j
        visited[last_point] = 1
        # 对首次循环做特殊处理，不然在首次循环时会没法求出该点的上一个顶点
        if i == 0:
            parents[last_point] = start + 1
        for k in range(node_num):
            if G[last_point][k] < inf and dis[k] > dis[last_point] + G[last_point][k]:
                # 如果有更短的路径，更新 dis 和 记录 parents
                dis[k] = dis[last_point] + G[last_point][k]
                parents[k] = last_point + 1

    # 因为从0开始，把顶点都加1
    return {key + 1: values for key, values in dis.items()}, {key + 1: values for key, values in parents.items()}

def read_txt_to_2d_list(file_path):
    result = []
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            result.append(line.strip().split())
    return result


if __name__ == '__main__':
    A = read_txt_to_2d_list('map.txt')
    G = [[float(x) for x in row] for row in A]
    '''
    G = [[0, 1, 12, inf, inf, inf],
         [inf, 0, 9, 3, inf, inf],
         [inf, inf, 0, inf, 5, inf],
         [inf, inf, 4, 0, 13, 15],
         [inf, inf, inf, inf, 0, 4],
         [inf, inf, inf, inf, inf, 0]]
    '''

    print("inf:无穷大")
    cal = np.zeros((6, 6))
    for i in range(1, 7):
        print("从v", i-1, "节点出发");
        dis, parents = Dijkstra(G, i)
        print("最短距离: ", dis)
        print("路径表: ", parents)
        my_list = [value for value in parents.values()]
        cal[i-1, :] = np.array(my_list)
    # 计算平均最短距离
    average = np.mean(cal[cal != -1])
    print("平均最短距离为", average)

    adj_matrix = np.array(G)
    print(adj_matrix)

    # 绘制图形
    x = [1, 0.5, -0.5, -1, -0.5, 0.5]
    y = [0, 0.866, 0.866, 0, -0.866, -0.866]
    plt.scatter(x, y)
    # 绘制节点名
    texts = ['v0', "v1", "v2", "v3", "v4", "v5"]
    for i in range(len(x)):
        plt.text(x[i], y[i], texts[i])

    v0v5 = [x[5] - x[0], y[5] - y[0]]
    v0v2 = [x[2] - x[0], y[2] - y[0]]
    v0v4 = [x[4] - x[0], y[4] - y[0]]
    v4v5 = [x[5] - x[4], y[5] - y[4]]
    v4v3 = [x[3] - x[4], y[3] - y[4]]
    v3v5 = [x[5] - x[3], y[5] - y[3]]
    v2v3 = [x[3] - x[2], y[3] - y[2]]
    v1v2 = [x[2] - x[1], y[2] - y[1]]
    # 箭头线
    plt.quiver(x[0], y[0], v0v5[0], v0v5[1], angles='xy', scale_units='xy', scale=1)
    plt.quiver(x[0], y[0], v0v2[0], v0v2[1], angles='xy', scale_units='xy', scale=1)
    plt.quiver(x[0], y[0], v0v4[0], v0v4[1], angles='xy', scale_units='xy', scale=1,color='r')
    plt.quiver(x[4], y[4], v4v5[0], v4v5[1], angles='xy', scale_units='xy', scale=1)
    plt.quiver(x[4], y[4], v4v3[0], v4v3[1], angles='xy', scale_units='xy', scale=1,color='r')
    plt.quiver(x[3], y[3], v3v5[0], v3v5[1], angles='xy', scale_units='xy', scale=1)
    plt.quiver(x[2], y[2], v2v3[0], v2v3[1], angles='xy', scale_units='xy', scale=1)
    plt.quiver(x[1], y[1], v1v2[0], v1v2[1], angles='xy', scale_units='xy', scale=1)

    plt.title("v0至v3的最短路径")
    plt.show()
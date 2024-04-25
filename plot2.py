import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
# # 定义外部大集装箱的参数
# container = {'x': 0, 'y': 0, 'z': 0, 'dx': 10, 'dy': 10, 'dz': 10}

# # 定义内部长方体的参数
# cuboids = [
#     {'x': 1, 'y': 1, 'z': 1, 'dx': 2, 'dy': 2, 'dz': 2},  # 长方体1
#     {'x': 4, 'y': 1, 'z': 1, 'dx': 1, 'dy': 2, 'dz': 3},  # 长方体2
#     {'x': 3, 'y': 3, 'z': 1, 'dx': 2, 'dy': 1, 'dz': 2},  # 长方体3
# ]
def randColor():
    color = np.random.rand(3,)  # Generates a random color as an RGB tuple
    return color

colors= ["red","blue"]
def plotCartons(alist:list,blist):
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    nowy = 0
    for i in range(len(alist)):
        alist[i]['y'] += nowy
        plotCarton(ax,alist[i],blist[i],nowy)
        # nowy += alist[i]['dy'] + 20
    # 设置图形的标签和视角
    ax.set_xlabel('X axis')
    ax.set_ylabel('Y axis')
    ax.set_zlabel('Z axis')
    ax.view_init(30, 45)
    # 显示图形
    plt.show()

def plotCarton(ax,container:dict,cuboids:list,nowy,Rcolor="red"):
    # 修改代码以区分外部大集装箱和内部长方体
    # 绘制外部大集装箱，不填充
    ax.plot([container['x'], container['x']+container['dx']], [container['y'], container['y']], [container['z'], container['z']], '-',color=Rcolor)
    ax.plot([container['x'], container['x']+container['dx']], [container['y']+container['dy'], container['y']+container['dy']], [container['z'], container['z']], '-',color=Rcolor)
    ax.plot([container['x'], container['x']+container['dx']], [container['y'], container['y']], [container['z']+container['dz'], container['z']+container['dz']], '-',color=Rcolor)
    ax.plot([container['x'], container['x']+container['dx']], [container['y']+container['dy'], container['y']+container['dy']], [container['z']+container['dz'], container['z']+container['dz']], '-',color=Rcolor)

    ax.plot([container['x'], container['x']], [container['y'], container['y']+container['dy']], [container['z'], container['z']], '-',color=Rcolor)
    ax.plot([container['x'], container['x']], [container['y'], container['y']+container['dy']], [container['z']+container['dz'], container['z']+container['dz']], '-',color=Rcolor)
    ax.plot([container['x']+container['dx'], container['x']+container['dx']], [container['y'], container['y']+container['dy']], [container['z'], container['z']], '-',color=Rcolor)
    ax.plot([container['x']+container['dx'], container['x']+container['dx']], [container['y'], container['y']+container['dy']], [container['z']+container['dz'], container['z']+container['dz']], '-',color=Rcolor)

    ax.plot([container['x'], container['x']], [container['y'], container['y']], [container['z'], container['z']+container['dz']], '-',color=Rcolor)
    ax.plot([container['x'], container['x']], [container['y']+container['dy'], container['y']+container['dy']], [container['z'], container['z']+container['dz']], '-',color=Rcolor)
    ax.plot([container['x']+container['dx'], container['x']+container['dx']], [container['y'], container['y']], [container['z'], container['z']+container['dz']], '-',color=Rcolor)
    ax.plot([container['x']+container['dx'], container['x']+container['dx']], [container['y']+container['dy'], container['y']+container['dy']], [container['z'], container['z']+container['dz']], '-',color=Rcolor)

    # 绘制内部填充的长方体
    for cuboid in cuboids:
        x, y, z = cuboid['x'], cuboid['y'] + nowy, cuboid['z']
        dx, dy, dz = cuboid['dx'], cuboid['dy'], cuboid['dz']
        # 使用bar3d绘制填充的长方体
        ax.bar3d(x, y, z, dx, dy, dz, color=randColor(), alpha=0.7)




def plotCartont(container:dict,cuboids:list):
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    print(container)
    # 绘制外部大集装箱，不填充
    ax.plot([container['x'], container['x']+container['dx']], [container['y'], container['y']], [container['z'], container['z']], 'k-')
    ax.plot([container['x'], container['x']+container['dx']], [container['y']+container['dy'], container['y']+container['dy']], [container['z'], container['z']], 'k-')
    ax.plot([container['x'], container['x']+container['dx']], [container['y'], container['y']], [container['z']+container['dz'], container['z']+container['dz']], 'k-')
    ax.plot([container['x'], container['x']+container['dx']], [container['y']+container['dy'], container['y']+container['dy']], [container['z']+container['dz'], container['z']+container['dz']], 'k-')

    ax.plot([container['x'], container['x']], [container['y'], container['y']+container['dy']], [container['z'], container['z']], 'k-')
    ax.plot([container['x'], container['x']], [container['y'], container['y']+container['dy']], [container['z']+container['dz'], container['z']+container['dz']], 'k-')
    ax.plot([container['x']+container['dx'], container['x']+container['dx']], [container['y'], container['y']+container['dy']], [container['z'], container['z']], 'k-')
    ax.plot([container['x']+container['dx'], container['x']+container['dx']], [container['y'], container['y']+container['dy']], [container['z']+container['dz'], container['z']+container['dz']], 'k-')

    ax.plot([container['x'], container['x']], [container['y'], container['y']], [container['z'], container['z']+container['dz']], 'k-')
    ax.plot([container['x'], container['x']], [container['y']+container['dy'], container['y']+container['dy']], [container['z'], container['z']+container['dz']], 'k-')
    ax.plot([container['x']+container['dx'], container['x']+container['dx']], [container['y'], container['y']], [container['z'], container['z']+container['dz']], 'k-')
    ax.plot([container['x']+container['dx'], container['x']+container['dx']], [container['y']+container['dy'], container['y']+container['dy']], [container['z'], container['z']+container['dz']], 'k-')

    # 绘制内部填充的长方体
    for cuboid in cuboids:
        x, y, z = cuboid['x'], cuboid['y'], cuboid['z']
        dx, dy, dz = cuboid['dx'], cuboid['dy'], cuboid['dz']
        # 使用bar3d绘制填充的长方体
        ax.bar3d(x, y, z, dx, dy, dz, color=randColor(), alpha=0.7)
    # 设置图形的标签和视角
    ax.set_xlabel('X axis')
    ax.set_ylabel('Y axis')
    ax.set_zlabel('Z axis')
    ax.view_init(30, 45)
    # 显示图形
    plt.show()

import sys
from plot2 import plotCarton,plotCartons,plotCartont
import copy
class rec:
    def __init__(self,_x,_y,_z,_dx,_dy,_dz,name:str = None):
        self.x = _x
        self.y = _y
        self.z = _z
        self.dx = _dx
        self.dy = _dy
        self.dz = _dz
        self.name = name
    def returnDict(self):
        return {
            'x':self.x,
            'y':self.y,
            'z':self.z,
            'dx':self.dx,
            'dy':self.dy,
            'dz':self.dz,
            'name':self.name
        }
class container:
    def __init__(self,carton:rec,box:list):
        self.carton = carton
        self.boxes = box
    def getDict(self):
        condic = carton.returnDict()
        boxdic = []
        for b in self.boxes:
            boxdic.append(b.returnDict())
        return condic,boxdic

# FDXFIRCV 0 0 0 26.74 7.14 0.28
with open("./docs/" + sys.argv[1],"r") as fp:
    line = fp.readline()
    num = eval(line)
    if num != 0:
        clist = []
        alist = []
        blist = []
        for i in range(num):
            lshape = fp.readline().split()
            carton = rec(0.0,0.0,0.0,float(lshape[0]),float(lshape[1]),float(lshape[2]))
            weight = eval(fp.readline())
            num2 = eval(fp.readline())
            boxlist = []
            for j in range(num2):
                line = fp.readline().split()
                box = rec(float(line[1]),float(line[2]),float(line[3]),float(line[4]),float(line[5]),float(line[6]),line[0])
                boxlist.append(box)
            clist.append(container(carton,boxlist))
            
            a,b = container(carton,boxlist).getDict()
            alist.append(a)
            blist.append(b)
    
    plotCartons(alist=alist,blist=blist)




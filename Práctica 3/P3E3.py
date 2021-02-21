import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

dataFile1 = np.loadtxt('P3E2_1k.txt', comments = '#')
dataFile2 = np.loadtxt('P3E2_10k.txt', comments = '#')
dataFile3 = np.loadtxt('P3E2_100k.txt', comments = '#')

dataFiles = [dataFile1, dataFile2, dataFile3]

pointPairs1k = list(zip(*[iter(dataFiles[0])] * 2))
pointPairs10k = list(zip(*[iter(dataFiles[1])] * 2))
pointPairs100k = list(zip(*[iter(dataFiles[2])] * 2))

pointPairs1kXCoord = []
pointPairs1kYCoord = []
pointPairs10kXCoord = []
pointPairs10kYCoord = []
pointPairs100kXCoord = []
pointPairs100kYCoord = []
pointTriples1kXCoord = []
pointTriples1kYCoord = []
pointTriples1kZCoord = []
pointTriples10kXCoord = []
pointTriples10kYCoord = []
pointTriples10kZCoord = []
pointTriples100kXCoord = []
pointTriples100kYCoord = []
pointTriples100kZCoord = []

for i in range(499):
    pointPairs1kXCoord.append(pointPairs1k[i][0])
    pointPairs1kYCoord.append(pointPairs1k[i][1])

for i in range(49999):
    pointPairs10kXCoord.append(pointPairs10k[i][0])
    pointPairs10kYCoord.append(pointPairs10k[i][1]) 

for i in range(499999):
    pointPairs100kXCoord.append(pointPairs100k[i][0])
    pointPairs100kYCoord.append(pointPairs100k[i][1])

pointTriples1k = list(zip(*[iter(dataFiles[0])] * 3))
pointTriples10k = list(zip(*[iter(dataFiles[1])] * 3))
pointTriples100k = list(zip(*[iter(dataFiles[2])] * 3))

for i in range(332):
    pointTriples1kXCoord.append(pointTriples1k[i][0])
    pointTriples1kYCoord.append(pointTriples1k[i][1])
    pointTriples1kZCoord.append(pointTriples1k[i][2])

for i in range(33332):
    pointTriples10kXCoord.append(pointTriples10k[i][0])
    pointTriples10kYCoord.append(pointTriples10k[i][1])
    pointTriples10kZCoord.append(pointTriples10k[i][2])

for i in range(333332):
    pointTriples100kXCoord.append(pointTriples100k[i][0])
    pointTriples100kYCoord.append(pointTriples100k[i][1])
    pointTriples100kZCoord.append(pointTriples100k[i][2])

print(pointPairs1kXCoord)    

pairFigure1 = plt.figure(1)
plt.scatter(pointPairs1kXCoord, pointPairs1kYCoord, 1)
plt.title("Pares 1000 puntos")
pairFigure1.show()

pairFigure2 = plt.figure(2)
plt.scatter(pointPairs10kXCoord, pointPairs10kYCoord, 1)
plt.title("Pares 10000 puntos")
pairFigure2.show()

pairFigure3 = plt.figure(3)
plt.scatter(pointPairs100kXCoord, pointPairs100kYCoord, 1)
plt.title("Pares 100000 puntos")
pairFigure3.show()

tripleFigure1 = plt.figure(4)
tripleAxes1 = Axes3D(tripleFigure1)
tripleAxes1.scatter3D(pointTriples1kXCoord, pointTriples1kYCoord, pointTriples1kZCoord, s = 1)
plt.title("Ternas 1000 puntos")
tripleFigure1.show()

tripleFigure2 = plt.figure(5)
tripleAxes2 = Axes3D(tripleFigure2)
tripleAxes2.scatter3D(pointTriples10kXCoord, pointTriples10kYCoord, pointTriples10kZCoord, s = 1)
plt.title("Ternas 10000 puntos")
tripleFigure2.show()

tripleFigure3 = plt.figure(6)
tripleAxes3 = Axes3D(tripleFigure3)
tripleAxes3.scatter3D(pointTriples100kXCoord, pointTriples100kYCoord, pointTriples100kZCoord, s = 1)
plt.title("Ternas 100000 puntos")
tripleFigure3.show()

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import glob
from scipy.optimize import curve_fit

myFiles = glob.glob('P4E1a*.txt')
myFiles
def exponential(x, a, b):
    return a*np.exp(-b*x)

temperature = np.linspace(0.5,6.0,len(myFiles))
tau = np.array([])

fig = plt.figure()
ax = fig
plt.title("\u03C4 vs T")
plt.xlabel("Temperatura")
plt.ylabel("\u03C4")

for fileName in myFiles:
    dataFile = np.loadtxt(fileName, comments = '#')
    popt = curve_fit(f=exponential, xdata=dataFile[:,0], ydata=dataFile[:,1], p0=[1, 0], bounds=(0, np.inf))
    #plt.scatter(dataFile[:,0], dataFile[:,1], s=3)
    tau = np.append(tau, popt[0][1])
tau
# xData = np.linspace(dataFile[0,0], dataFile[-1,0], 10000)
# yData = exponential(xData, popt[0][0], popt[0][1])
# labelName = "tau = " + str(1/popt[0][1])
# plt.plot(xData, yData, label=labelName)
# ax.legend(bbox_to_anchor=(0.87, 0.85))

plt.scatter(temperature, tau, s=4)

plt.show()
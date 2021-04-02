import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.optimize import curve_fit

dataFile = np.loadtxt('P4E2_autocorrTime_N=100_h=0.000000.txt', comments = '#', usecols = range(1,1000))

tempArray = np.loadtxt('P4E2_autocorrTime_N=100_h=0.000000.txt', comments = '#', usecols = 0)

autocorrTime = np.zeros(len(tempArray))

fig = plt.figure()
ax = fig
plt.title("Autocorrelación, N=100, h=0")
plt.xlabel("Temperatura")
plt.ylabel("Tiempo de autocorrelación")

def exponential(x, a, b):
    return a*np.exp(-b*x)

timeData = np.linspace(0, len(dataFile[0,:]), len(dataFile[0,:]))

for i in range(len(tempArray)):
    popt = curve_fit(f=exponential, xdata=timeData, ydata=dataFile[i,:], p0=[1, 0], bounds=(0, np.inf))
    autocorrTime[i] = popt[0][1]
    # plt.scatter(timeData, dataFile[i,:]/dataFile[i,0], s=2)

plt.scatter(tempArray, autocorrTime, s=3)
plt.show()
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import glob
from scipy.optimize import curve_fit
from matplotlib.widgets import Slider, Button, RadioButtons

myFiles = glob.glob('P4E4_suscep_N*h=1*')
fig = plt.figure()
ax = fig
plt.title("h=1")
plt.xlabel("t*L")
plt.ylabel("\u03C7*L^(-7/4)")
critTemp = 2 / np.log(1 + np.sqrt(2))
array = [10, 20, 50, 5]

plt.axvline(x=4.3)

for i in range(4):
    dataFile = np.loadtxt(myFiles[i], comments = '#')
    cleanName = myFiles[i].strip(".txt")[:-7].split("_")
    plt.scatter(dataFile[:,0], dataFile[:,1], s=5, label=cleanName[2])
    #plt.scatter(np.abs(dataFile[:,0]-critTemp) * array[i] / critTemp , dataFile[:,1] * pow(array[i], -7/4), s=5, label=cleanName[2])
    # plt.plot(dataFile[:,0], dataFile[:,1], label=cleanName[2])
    ax.legend(bbox_to_anchor=(0.87, 0.85))

plt.show()

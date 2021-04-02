import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

dataFile1 = np.loadtxt('P4E2_E_N=30_h=1.000000.txt', comments = '#')
dataFile2 = np.loadtxt('P4E2_cv_N=30_h=1.000000.txt', comments = '#')
dataFile3 = np.loadtxt('P4E2_M_N=30_h=1.000000.txt', comments = '#')
dataFile4 = np.loadtxt('P4E2_suscep_N=30_h=1.000000.txt', comments = '#')

energyFigure = plt.figure(1)
plt.scatter(dataFile1[:,0], dataFile1[:,1], s = 1)
plt.axvline(x=2.269, color = 'c')
plt.title("Energía vs Temperatura, N=30, h=1")
plt.errorbar(dataFile1[:,0], dataFile1[:,1],yerr=dataFile1[:,2], fmt='.')
energyFigure.show()

specHeatFigure = plt.figure(2)
plt.scatter(dataFile2[:,0], dataFile2[:,1], s = 1)
plt.axvline(x=2.269, color = 'c')
plt.title("Calor especifico vs Temperatura, N=30, h=1")
plt.errorbar(dataFile2[:,0], dataFile2[:,1],yerr=dataFile2[:,2], fmt='.')
specHeatFigure.show()

magnetFigure = plt.figure(3)
plt.scatter(dataFile3[:,0], dataFile3[:,1], s = 1)
plt.axvline(x=2.269, color = 'c')
plt.title("Magnetización vs Temperatura, N=30, h=1")
plt.errorbar(dataFile3[:,0], dataFile3[:,1],yerr=dataFile3[:,2], fmt='.')
magnetFigure.show()

suscepMagnetFigure = plt.figure(4)
plt.scatter(dataFile4[:,0], dataFile4[:,1], s = 1)
plt.axvline(x=2.269, color = 'c')
plt.title("Susceptibilidad magnetica vs Temperatura, N=30, h=1")
plt.errorbar(dataFile4[:,0], dataFile4[:,1],yerr=dataFile4[:,2], fmt='.')
suscepMagnetFigure.show()
import numpy as np
import matplotlib.pyplot as plt

dataFile = np.loadtxt('P3E4a.txt', comments = '#')
average = np.zeros(len(dataFile[:,0]))
average2 = np.zeros(len(dataFile[:,0]))
autocorr = np.zeros(len(dataFile[:,0]))
autocorr2 = np.zeros(len(dataFile[:,0]))
newRandomSequence = np.zeros((len(dataFile[:,0]), len(dataFile[0,:])))

# Formula (35) de Grigera T. "Everything you wish to know about time correlations but are afraid to ask" 

for i in range(len(dataFile[:,0])):
    for j in range(len(dataFile[0,:])):
        average[i] += dataFile[i,j] / len(dataFile[0,:])

for i in range(len(dataFile[:,0])):
    for j in range(len(dataFile[0,:])):
        autocorr[i] += dataFile[0,j] * dataFile[i,j] / len(dataFile[0,:])
    autocorr[i] -= average[i]*average[0]

Figura1 = plt.figure(1)
plt.plot(autocorr, linewidth=0.4)
Figura1.show()

w = 0.9

for i in range(len(dataFile[0,:])):
    newRandomSequence[0,i] = dataFile[0,i]
    for j in range(1, len(dataFile[:,0])):
        newRandomSequence[j,i] = w * newRandomSequence[j - 1,i] + (1 - w) * dataFile[j,i]

for i in range(len(dataFile[:,0])):
    for j in range(len(dataFile[0,:])):
        average2[i] += newRandomSequence[i,j] / len(dataFile[0,:])

for i in range(len(newRandomSequence[:,0])):
    for j in range(len(newRandomSequence[0,:])):
        autocorr2[i] += newRandomSequence[0,j] * newRandomSequence[i,j] / len(newRandomSequence[0,:])
    autocorr2[i] -= average2[i]*average2[0]

Figura2 = plt.figure(2)
plt.plot(autocorr2, linewidth=0.4)
Figura2.show()

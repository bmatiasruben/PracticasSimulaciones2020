import numpy as np
import matplotlib.pyplot as plt

dataFile1 = np.loadtxt('P3E2_1k.txt', comments = '#')
dataFile2 = np.loadtxt('P3E2_10k.txt', comments = '#')
dataFile3 = np.loadtxt('P3E2_100k.txt', comments = '#')

histogramaa1 = plt.figure(1)
plt.hist(dataFile1, bins = 1000)
plt.title("Histogramaa 1000 datos")
histogramaa1.show()

histogramaa2 = plt.figure(2)
plt.hist(dataFile2, bins = 1000)
plt.title("Histogramaa 10000 datos")
histogramaa2.show()

histogramaa3 = plt.figure(3)
plt.hist(dataFile3, bins = 1000)
plt.title("Histogramaa 100000 datos")
histogramaa3.show()

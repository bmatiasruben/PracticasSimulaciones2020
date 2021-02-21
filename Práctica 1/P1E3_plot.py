import numpy as np
import matplotlib.pyplot as plt

data_file1 = np.loadtxt('Pi_vs_N_Ej3.txt', comments = '#')

plt.scatter(10**data_file1[:,0], data_file1[:,1])
plt.title("Pi vs N")
plt.xscale('log')
plt.show()

import numpy as np
import matplotlib.pyplot as plt

data_file1 = np.loadtxt('Var_vs_N_Ej1.txt', comments = '#')
data_file2 = np.loadtxt('Pi_vs_N_Ej1.txt', comments = '#')

f = plt.figure(1)
plt.scatter(10**data_file1[:,0], data_file1[:,1])
plt.title("Varianza vs N")
plt.xscale('log')
f.show()

g = plt.figure(2)
plt.scatter(10**data_file1[:,0], data_file2[:,1])
plt.title("Pi vs N")
plt.xscale('log')
g.show()

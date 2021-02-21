import numpy as np
import matplotlib.pyplot as plt

data_file1 = np.loadtxt('Var_vs_delta_Ej2.txt', comments = '#')
data_file2 = np.loadtxt('Accept_vs_delta_Ej2.txt', comments = '#')
data_file3 = np.loadtxt('Pi_vs_N_Ej2.txt', comments = '#')

f = plt.figure(1)
plt.scatter(data_file1[:,0], data_file1[:,1])
plt.title("Varianza vs delta")
plt.yscale('log')
f.show()

g = plt.figure(2)
plt.scatter(data_file2[:,0], data_file2[:,1])
plt.title("Acceptacion vs delta")
plt.yscale('log')
g.show()

h = plt.figure(3)
plt.scatter(10**data_file3[:,0], data_file3[:,1])
plt.title("Pi vs N")
plt.xscale('log')
h.show()
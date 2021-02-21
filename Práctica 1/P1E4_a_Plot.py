import numpy as np
import matplotlib.pyplot as plt

data_file1 = np.loadtxt('Prob_vs_Celda_Ej4.txt', comments = '#')
# data_file2 = np.loadtxt('Accept_vs_delta_Ej2.txt', comments = '#')

f = plt.figure(1)
plt.scatter(data_file1[:,0], data_file1[:,1])
plt.title("Probabilidad vs Celda (N = 10^3)")
plt.ylim(bottom = 0, top = 0.3)
f.show()

# g = plt.figure(2)
# plt.scatter(data_file2[:,0], data_file2[:,1])
# plt.title("Acceptacion vs delta")
# plt.yscale('log')
# g.show()
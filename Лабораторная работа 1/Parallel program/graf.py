import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

data = np.genfromtxt('output.csv', delimiter=',')

x = data[:, 0]
t = data[:, 1]
u = data[:, 2]

u = u.reshape((int(len(u)/(len(x))), len(x)))
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.set_xlabel('x')
ax.set_ylabel('t')
ax.set_zlabel('U(t,x)')

ax.plot_surface(np.tile(x, (len(t), 1)), np.tile(t, (len(x), 1)).T, u)
plt.show()


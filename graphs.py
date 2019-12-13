# Copyright 2019 Grama Nicolae
import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np

filename="./other_tests/time.csv"

data = np.genfromtxt(filename, names=True, dtype=int, delimiter=",")

plt.plot(data["nodes"], data["times"], marker='o');
plt.title("Timp de executie")
plt.ylabel("Timp (ms)")
plt.xlabel("Numar de noduri")
plt.grid()
plt.savefig('./Images/Complexitate.png')
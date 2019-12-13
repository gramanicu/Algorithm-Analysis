# Copyright 2019 Grama Nicolae
import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np

dijkstra_file ="./other_tests/dtime.csv"
floyd_file ="./other_tests/ftime.csv"
johnson_file ="./other_tests/jtime.csv"
best_file ="./other_tests/btime.csv"

# Load data
dijkstra = np.genfromtxt(dijkstra_file, names=True, dtype=int, delimiter=",")
floydwarshall = np.genfromtxt(floyd_file, names=True, dtype=int, delimiter=",")
johnson = np.genfromtxt(johnson_file, names=True, dtype=int, delimiter=",")
best = np.genfromtxt(best_file, names=True, dtype=int, delimiter=",")

# Plot all data
plt.plot(dijkstra["nodes"], dijkstra["times"], marker='o', label="Dijkstra");
plt.plot(floydwarshall["nodes"], floydwarshall["times"], marker='x', label="Floyd-Warshall");
plt.plot(johnson["nodes"], johnson["times"], marker='h', label="Johnson");

axes = plt.gca()
# axes.set_ylim([0, 1000])

plt.title("Complexitate")
plt.ylabel("Timp (ms)")
plt.xlabel("Numar de noduri")
plt.legend()
plt.grid()

fig = matplotlib.pyplot.gcf()
fig.set_size_inches(18.5, 10.5)
fig.savefig('./Images/ComplexitateComparata.png')

plt.clf()

# Plot only Dijkstra
plt.plot(dijkstra["nodes"], dijkstra["times"], marker='o', label="Dijkstra");
plt.title("Complexitate")
plt.ylabel("Timp (ms)")
plt.xlabel("Numar de noduri")
plt.grid()
plt.savefig('./Images/ComplexitateDijkstra.png')
plt.clf()

# Plot only Floyd-Warshall
plt.plot(floydwarshall["nodes"], floydwarshall["times"], marker='x', label="Floyd-Warshall");
plt.title("Complexitate (*pentru mai mult de 2000 noduri, algoritmul nu ruleaza)")
plt.ylabel("Timp (ms)")
plt.xlabel("Numar de noduri")
plt.grid()
plt.savefig('./Images/ComplexitateFloydWarshall.png')
plt.clf()

# Plot only Johnson
plt.plot(johnson["nodes"], johnson["times"], marker='h', label="Johnson");
plt.title("Complexitate")
plt.ylabel("Timp (ms)")
plt.xlabel("Numar de noduri")
plt.grid()
plt.savefig('./Images/ComplexitateJohnson.png')
plt.clf()

# Plot the best algorithm
plt.plot(best["nodes"], best["times"], marker='D', label="Best");
plt.title("Complexitate")
plt.ylabel("Timp (ms)")
plt.xlabel("Numar de noduri")
plt.grid()
plt.savefig('./Images/ComplexitateBest.png')
plt.clf()
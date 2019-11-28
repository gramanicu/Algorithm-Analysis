# Graph Generator

This is a helper program, used to generate graphs. It is used to test algorithms that find the shortest distance between all nodes in a graph. It generatest two types of files:

- Input Files - These files contain the number of nodes in the graph, the number of edges, and a list of edges. They have the following format:
  
```c
node_count edge_count
source_node_1 target_node_1 edge_cost_1
source_node_2 target_node_2 edge_cost_2
source_node_3 target_node_3 edge_cost_3
...
source_node_k target_node_k edge_cost_k
...
```

- Reference Files - These files contain the solution for the graph (shortest paths), in matrix form.
  
```c
dist_nodes11 dist_nodes12 ... dist_nodes1k ...
dist_nodes21 dist_nodes22 ... dist_nodes2k ...
...
dist_nodesk1 dist_nodesk2 ... dist_nodeskk ...
...
```

The distance from a node to itself can have 2 values :

1. 0 - normal graph
2. A negative value - it means the graph contains a negative cycle

## Constants

The generator needs to use some constants, like:

- `INPUTS_FOLDER` - the folder where to store input files
- `REFERENCE_FOLDER` - the folder where to store reference files
- `MAX_NODES` - the maximum number of nodes in a graph. The time to generate the graphs increases rapidly as the number of nodes is increased, so it shouldn't be changed from it's default value of 250.
- `MAX_NODES_POSITIVE` - in the case when we have only positive costs in the graph, we can generate bigger graphs much faster. The value of 400 seems to be a good tradeoff between speed and graph complexity.
- `MAX_CYCLE_TRIES` - the way this program removes negative cycles is by keeping on generating graphs untill it doesn't contain negative cycles. However, for a bigger graph, the chances of success are much lower, so we need to limit how many times the program will retry to build the graph.

## Settings

There are 4 settings that alter the way a graph is generated:

1. has_negative - if the graph has negative costs
2. only_unit - if the graph has `|cost| = 1`
3. fully_random - if we want the costs to be fully randomised. If not, the numbers are still random, but they are picked to not exceed the number of nodes/edges
4. negative_cycles - if the graph will contain negative cycles. As specified earlier, this is the only thing that is not guaranteed to happen. If we activate this setting, we can see if the task succeded/failed in `positive.txt`/`negative.txt` files

These settings are used in `generate.in` file. The format of the file is the following :

```c
number_of_tests_bulks
number_of_tests has_negative only_unit fully_random negative_cycles
...
```

Take the following example :

```c
3
75 0 1 0 1
100 1 0 1 0
25 0 0 0 0
```

Will generate 3 test "bulks" :

- 75 tests with all costs equal to 1, and will permit negative cycles (althought it's impossible to happen)
- 100 tests with costs in the `INT32_MIN` -> `INT32_MAX - 1` interval,  (`INT32_MAX` is considered `infinity`), and will not permit negative cycles
- 25 tests with positive random values (not fully randomised), and will not permit negative cycles (they won't happen anyway)

## Building solution - Floyd Warshall

I chose this algorithm to generate the reference files because it is simple to implement, and it can also detect negative cycles. It's only drawback is the fact that is quite an inneficient algorithm, but it isn't a problem in this specific use case.

After it computes the `distance matrix`, it can detect negative cycles by checking the diagonal of the matrix for negative values.

## RNG - EasyRand

This program uses a [library](https://github.com/gramanicu/EasyRand) I developed some time ago, to generate random numbers. It solves some [problems](https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful) that more common randomisation methods like `rand()` or `srand()` have.

I preffered to use the .cpp and .h files directly, as importing the library and compiling it would have made the project structure too complex.

## Makefile

The essential commands included are:

- `build` - compiles the code and generates the executable ("Generator")
- `run` - compiles, then runs the binary
- `clean` - deletes all binaries and object files
- `cleanAll` - deletes all binaries, object files and generated files

For development and testing purposes, the makefile includes some other commands:

- `beauty` - beautifies the code, using the google standard
- `memory` - runs valgrind on the code

The makefile will hide some of the output and show custom messages (for example the "build" command)

## References

- GeeksForGeeks - [Detecting negative cycle using Floyd Warshall](https://www.geeksforgeeks.org/detecting-negative-cycle-using-floyd-warshall/)

© 2019 Grama Nicolae, 322CA

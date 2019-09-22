A Python implementation for the Dijkstra's shortest path algorithm.

# Dijkstra's Algorithm

Dijkstra's algorithm, developed by computer scientist Edsger W. Dijkstra, is an algorithm for finding the shortest paths between all the nodes in a graph.

The algorithm runs on a weighted graph, and works by finding, from an initial node A, the least cost path to a goal node B.

# Input File

The input file must contain the description of a weighted graph with one connected component, and without negative weights. For each line of the file, the first two digits *a* and *b* represents the edge between vetice **a** and **b**, whereas the third digit represent the edge weight.

```py
# input_graph.txt

0 1 6
0 3 1
1 2 5
1 3 2
1 4 2
2 4 5
3 4 1
```

# Compiling (Linux terminal)

```py
python dijkstra.py input_graph.txt
```

# Expected Output

The script outputs the shortest path between any two vertices in the graph.

```
Shortest path betweem any two vertices: 
[0, 3, 4, 1, 2]
```

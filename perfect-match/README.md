A C implementation of Tutte's Theorem for checking Perfect Matchings in a graph.

## Matching
In the mathematical discipline of **Graph Theory** the concept of **Matching** is defined as a set of *edges* without common vertices. Given a graph *G=(V,E)*, where *V* is the set of vertices and *E* is the set of edges, a matching **M** in **G** is a set of pairwise non-adjacent edges, none of which are loops; that is, no two edges share a common vertex. A vertex is said to be *saturated* if it is an endpoint of one of the edges in the matching.

Matchings can be of three kind:

* **MAXIMAL** - a matching **M** of a graph **G** with the property that if any edge not in M is added to M, it is no longer a matching, that is, M is maximal if it is not a subset of any other matching in graph G.

* **MAXIMUM** - a matching that contains the largest possible number of edges. The **Matching Number** of a graph is the size of a maximum matching. Note that every maximum matching is maximal, but not every maximal matching is a maximum matching.

* **PERFECT** - a matching which matches all vertices of the graph (every vertex is saturated). That is, every vertex of the graph is incident to exactly one edge of the matching. Every perfect matching is maximum and hence maximal.

## Tutte's Theorem

The Tutte's Theorem, named after William Thomas Tutte, is a theorem that characterizes graphs having perfect matchings. The theorem states the following:

*"A graph, **G = (V, E)**, has a perfect matching if and only if for every subset **U** of **V**, the subgraph induced by V − U has at most |U| connected components with an odd number of vertices."*

## Usage

## Before Compilation

As this code utilizes sequential arrays within it, the number of vertices must be set at the beginning of the main file, in the **MAX** global constant:

```c
/* main.c */
#define MAX 4   /* Number of vertices in the graph */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "matrix_temp.h"    

int main(int argc, char *argv[]) 
{
    ...
```

### Compile (Linux)
**gcc main.c -o output_file**

### Input File

An input file containing a graph graph must be provided as argument. The graph must be described as follows.

```c
/* input_file.txt */

4       /* Number of vertices (|V|) */
0 1     /* Edge between vertex 0 and 1 */
0 3     /* ... */
1 2
2 3
```

### Execution
**./output_file input_file.txt**

### Expected Output

```c
Adjacency Matrix: /* Adjacency matrix of the input graph */
========================================
0 1 0 1 
1 0 1 0 
0 1 0 1 
1 0 1 0 
========================================
Result: G HAS a Perfect Matching M.
```

# Contact

In case of any bugs and/or sugestions, send an email to wsg@icomp.ufam.edu.br or williansoaresgirao@gmail.com.



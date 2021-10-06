Ruchit Patel

---------------------
DESCRIPTION

- In this lab, the Traveling Salesman Problem (TSP) is implemented using a graph (adjacency matrix) and depth-first search (DFS) algorithm.
- A Graph (directed or undirected) is represented by an adjacent matrix of VERTICES vertices (in this case 26).
- DFS is ran from a STARTVERTEX (in this case 0) until a shortest hamiltonian path is found.
- Arguments:    -u (Use undirected graph),
                -v (Enables verbose printing (prints all shortest paths)), 
		-h (prints help message), 
		-i (specifies input file (default:stdin)), 
		-o (specifies output file (default:stdout)), 

---------------------
FILES

1. tsp.h
- This is a header file that declares the dfs print method to be used inside dfs.

2. tsp.c 
- This source file contains main and handles input/output, error handling (done throughout), sets up, calls, and cleans up after dfs.

3. dfs.h
- This header file declares rec call extern variable (for keeping track of recursive calls) and declares dfs function (to be called from main in tsp).

4. dfs.c 
- This source file implements the dfs method.

5. vertices.h
- This header file declares macros for vertices such as START VERTEX and VERTICES mentioned above.

6. graph.h
- This header file declares the graph abstract data structure and the methods to manipulate it.

7. graph.c 
-  This source file implements the methods declared in graph.h to work with a graph.

8. path.h
- This header file declares the path abstract data structure and the methods to manipulate it.

9. path.c 
-  This source file implements the methods declared in path.h to work with a path.

10. stack.h
- This header file declares the stack abstract data structure and the methods to manipulate it.

11. stack.c 
-  This source file implements the methods declared in stack.h to work with a stack.

12. set.h
- This header file is an interface for the set ADT as described above.

13. set.c
- This file contains implementation of set ADT which is used as a bitmask for arguments.

14. DESIGN.pdf 

- This PDF explains the design for this lab. It includes a brief description of the lab and pseudocode alongwith implementation description. 

15. Makefile

- This is a Makefile that can be used with the make utility to build the executable.


---------------------
INSTRUCTIONS

Manually:
1. Keep all the source and header files in the same directory and compile the source files using clang compiler in Ubuntu 20.04.

2. The documented compilation command is as follows: clang -Wall -Wextra -Wpedantic -Wshadow -o tsp *.c 

3. Finally, execute ./tsp -[arguments] in a terminal. 

4. The program would run as described in the description based on the arguments. 


With make:
1. Keep the Makefile in the same directory as all other files mentioned above.

2. Execute “make” or “make all” in terminal in order to produce the tsp executable. 

3. Finally, execute ./tsp -[arguments] in a terminal. 

4. The program would run as described in the description based on the arguments. 

5. In order to scan-build the source file, run “make scan-build” in the terminal.

6. In order to clean up (remove object and executable files), run “make clean” in the terminal.

This is a part of lab designed by Prof. Darrell Long.

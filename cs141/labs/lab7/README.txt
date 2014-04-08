
--- finding a shortest path between two nodes ---

PROBLEM DEFINITION:

Your program will read in a textual representation of a maze from
standard input.  See for example ./Mazes/wtd_maze_010.txt .  '#'
characters represent walls.  Digits in the text represent open cells
in the maze.  The digit in an open cell represents the "cost" 
of going through the cell.  Two open cells are adjacent
(that is, you can get directly from one to the other) if one is to the
left, to the right, above, or below the other (but not diagonally).

Your program will find a path from the upper left corner 
of the maze to the lower right corner.   THE PATH MUST BE 
A PATH OF MINIMUM TOTAL COST (minimizing the sum, over the
cells on the path, of the digit associated with the cell).
It will output the total node weight along such a path.

FURTHER INSTRUCTIONS:

The following files are given in the framework:

   Mazes/*

The existing code builds a graph from the textual representation
of the maze.  The graph has a node for each cell, and
edges between nodes representing adjacent cells.  Each node
has a "weight" equal to the digit in the corresponding cell.

You should complete the code for the function find_distance().
You can base find_distance on Dijkstra's algorithm, but you will
have to figure out how to modify that algorithm to deal with
weights on the nodes (instead of weights on the edges, which is
what Dijkstra's algorithm usually works with).

Note that the pre-existing code already builds the graph 
data structure for you.  You do not need to write code to
do that.  The find_distance() routine is passed the start and end node.

You can test your routine by running it with the shell command
$ ./find_distance.py <Mazes/wtd_maze_003.txt
and comparing the output to the contents of Mazes/soln_maze_003.txt
(and likewise for other Mazes/wtd_maze_*.txt files).

When you are satisfied that your solution is correct,
turn in the SINGLE FILE find_distance.py

Python notes:
You might find heap data structure useful. The heap in python library is a
min-heap but does not support decrease key. You can still use it for Dijkstra's
algorithm with lazy deletion. In this implementation decrease-key is simulated
with inserting a new (dist, node) pair into heap while also checking whether the
node popped from heap has been processed before, and skip if so. You can use
seen[][] for this purpose.
http://docs.python.org/library/heapq.html

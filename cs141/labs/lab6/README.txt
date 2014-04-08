--- finding a path between two nodes ---

PROBLEM DEFINITION:

Your program will read in a textual representation of a maze from standard input.
See for example ./Mazes/maze_010.txt .  ' ' characters in the
text represent open cells in the maze.  '#' characters represent walls.
Two open cells are adjacent (that is, you can get directly from one to the 
other) if one is to the left, to the right, above, or below the other 
(but not diagonally).

Your program will build a graph from the textual representation
of the maze.  The graph will have a node for each cell, and
edges between nodes representing adjacent cells.

Your program will find a path from the upper left corner (the leftmost ' ' on
top row) of the maze to the lower right corner (the rightmost ' ' on bottom
row). It will output the maze, with the nodes on the path labeled with their
distance to the destination (mod 10), as well as the length of the path found.
If a cell is not reachable from the start cell, output ' ' if it is a ' ' cell,
output '#' if it is a '#' cell. See Mazes/ for soln examples.

INTRUCTIONS:

+ Due May 15, Tue 10pm
+ There is NO python source to start with, create your own python program.
+ Test with command
    chmod +x lab6.py
    ./lab6.py <Mazes/maze_xxxx.txt >output.txt  # use the actual filename to
    replace xxxx

- Call your python source lab6.py
- To read the input
import sys
graph = sys.stdin.readlines()
# graph will be a list of strings with each string being a row
# use BFS to find distance from the start cell to each other cell
# the start cell is the leftmost ' ' on top row
# the end cell is the rightmost ' ' on the bottom row

- You can use a pair (r,c) to represent a node.

- To go from node (r,c) to its four neighbors, loop over an array d=[(-1,0),
  (0,+1), (+1,0), (0,-1)]

- Output 
print a 2D array, with each element being the distance from the start cell to
the cell (dist modulo 10). If a cell is not reachable from the start cell,
output ' ' if it is a ' ' cell, output '#' if it is a '#' cell. See Mazes/ for
soln examples.  print on a separate line the distance from the start cell to the
end cell.

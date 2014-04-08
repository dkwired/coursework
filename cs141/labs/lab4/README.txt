LAB ASSIGNMENT 4

LAB 4 ASSIGNMENT:

The first part of the lab meeting will be spent in group discussion
with the TA at the whiteboard, not sitting at the computer.

The second half will be spent doing the following on the computer:
Download and unpack the .zip archive.  Inspect the files.

Note that the provided "LargeInt" class allows you to do arithmetic
with arbitrarily large integers.  Basic arithmetic operations are
provided already for this class.

Finally, use gnuplot or a spreadsheet program, to plot the running
time versus the number of bits in the input.  Find the best constant C
that you can such that the plot of the running time data falls along
the curve C*(number of bits)^1.59.

TURN-IN INSTRUCTIONS 

In the file ./solutions.txt, record the value of C that you found.

Then, in the terminal window, run the command "make turnin" to create
an archive named "lab4_turnin.zip" containing the source files in the
directory.  Turn that file in in the lab4 turn-in on moodle.

(Note: the "make turnin" command will first clean your
directory of any .o files and executables, this is 
intentional to keep the size of the turn-in archive small.)

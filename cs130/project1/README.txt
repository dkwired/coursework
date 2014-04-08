David Klein
860880864
CS 130
Fall 2013

README for Project 1

To run a the program:

The program is hard coded to only subdivide for 3 recursions. If you want to do more, you will need to hardcode this value by editing:

Subdivision(POINTS[face.a], POINTS[face.b], POINTS[face.c], 2, 0);

By replacing the "2" you can do more recurions if you like. Unfortunately I could not get the keyboard input to work in order to swap between Front, Side, and Top rendering. To render a file on a specific face, enter from the command line:

Front.out < samplemeshes/sampletri.txt

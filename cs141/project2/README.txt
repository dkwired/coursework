David Klein
860880864
CS 141
Fall 2013
Project 2

Implementation:

For my implementation I designed a helper matrix class. This class was designed to create a m x n matrix. The user would then be able to fill that matrix with a string (row by row). Once the matrix is full I could then run my FindSquare algorithm to find the largest square within that matrix. My algorithm for finding the largest square is as follows:

FindSquare(x, y) = { 	0 if x or y = 0
			min {	FindSquare(i-1, y)
				FindSquare(i, y-1)
				FindSquare(i-1,y-1) } }

This algorithm will trace back through the "constructed" matrix and look for the minimum path to reach our base case. Since the "construction" of the matrix is m x n, our worst case run time is O(mn).

Errors:

Unfortunately I was not able to figure out how to get the 2nd largest square since my algorithm only outputs the dimension of the largest square. Also, I do get a bunch of pointer warnings when building, which I was not able to resolve. Also, my main function is only able to read in the first matrix, eventhough I have a loop that tells it there are more matrices to read. Because of my design I was only able to output one answer at a time. This meant that I had to append to a file for each output. So, if there is a file that already exists the output will be appended to it. If I was running multiple input files it would be hard to decipher which output came from which input file (unless I kept track of the order). In retrospect, working with Python would have been easier.


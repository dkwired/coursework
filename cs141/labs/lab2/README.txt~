LAB ASSIGNMENT 2, DUE TUESDAY NIGHT(10pm), APRIL 17

If you have any questions or comments, please feel free
to contact the TA or the instructor.

LAB 2 ASSIGNMENT:

The first part of the lab meeting will be spent in group discussion
with the TA at the white board, not sitting at the computer.

The second half will be spent doing the following on the computer:
Download and unpack the .zip archive.  Inspect the files.

Python does arbitrary precision integer arithmetic and integers will be
converted into arbitrary precision whenever necessary hence no integer
overflow concerns when programming in python.

In a terminal window, in the directory created by the unzipping the 
archive, type "./slow_exp.py 2025 119 8633", which should output 
(2025^119 mod 8633).

In the file fast_exp.py, replace the body of the function
fast_exp(x,y,N) with code that implements one of the two
fast modular exponentiation algorithms discussed in class
(the recursive one, or the iterative repeated squares algorithm).  
Your implementation should run in O(n^3) time, if given n-bit integers,
assuming multiplication of integers takes O(n^2) time.

When you are done implementing your algorithm, do the following
commands in a terminal window to test it out:

$ ./fast_exp < test-inputs.txt
$ ./fast_exp < test-inputs-large.txt

QUESTION 1:

a) Using fast_exp, what is the largest input (in terms of bits)
that "fast_exp.py" tries, for which fast_exp can compute 
the answer in under a second?

b) Is the running time of fast_exp polynomial in the size
(number of bits) of its inputs?  Explain.  In answering
this question, you can assume that the arithmetic operations
take time O(n) (for addition)
and O(n^2) (for multiplication) on n-bit integers.

(bonus question (c): if you plot the actual time taken, versus
the input size in bits, for the examples tried by the command 
"fast_exp.py", what curve does the running time
seem to fit?  You can use gnuplot or a spreadsheet
to do the plot.)


QUESTION 2:

For the input that was your answer to question 1(a),
if you were to instead use slow_exp to calculate x^y mod N,
estimate how long it would take (in seconds, hours, days, 
months, years, etc.) to compute x^y mod N.

Explain your reasoning.

(Assume multiplications take time c*n^2 seconds for some c.
Since slow_exp(x,y,N) does y multiplications, the running
time of slow_exp(x,y,N) should be about c*y*n^2.  You can
estimate c (on your computer) by the running time for
moderate values of n.  Once you have this estimate, you can
predict that the running time for any (x,y,N) will be about
c*y*n^2...)

If you try various inputs, does your estimate seem accurate?

TURN-IN INSTRUCTIONS 
(TURN IN BY THE DUE DATE TUESDAY NIGHT, APRIL 17):

Put your answers to the above questions in the file solutions.txt
or in a file solutions.pdf in this directory. Submit it along with 
fast_exp.py to ilearn.

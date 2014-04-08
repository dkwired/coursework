
LAB ASSIGNMENT 1, DUE TUESDAY NIGHT, APRIL 10

If you have any questions or comments, please feel free
to contact TA lyan@cs.ucr.edu or the instructor neal@cs.ucr.edu.

SUGGESTIONS:

LAB 1 ASSIGNMENT:

The first half of each lab meeting will be spent in group discussion
with the TA at the whiteboard, not sitting at the computer.

The second half will be spent doing the following on the computer:
Download and unpack the .zip archive.
Inspect the files fib1.py, fib2.py

In a terminal window (using the shell):
    chmod +x fib1.py
    ./fib1.py
the output is running time in seconds, that is, if the output is 0.56, it
means the program runs in 0.56 seconds.

Figure out what two algorithms the two routines fib1() and fib2() implement.
For fib2, it may help to add print statements or use the debugger.

QUESTION 1:

a) Using fib1, what is the largest n for which you can compute the nth fibonacci 
number in under a minute?

b) Consider the recursion diagram for fib1(N).  

By the "depth" of a particular recursive call to fib1(N),
we mean the number of calls above fib1(N) in the call stack.

For example, calling fib1(4) results in the following recursive calls:

fib1(4)
|-fib1(3)
| |-fib1(2)    <-- this call to fib1(2) has depth 2
| | |- fib1(1)
| | |- fib1(0)
| |
| |-fib1(1)    <-- this call to fib1(1) has depth 2
|
|-fib1(2)      <-- this call to fib1(2) has depth 1
  |- fib1(1)
  |- fib1(0)

If N is even, and you call fib1(N), during its execution,
how many recursive calls are there at depth N/2?
(For example, are there Theta(N), Theta(N^2), Theta(N^N)?)
Explain your reasoning.

c) Is the running time of fib1(N) polynomial in N?  
Try to justify your answer rigourously.


QUESTION 2:

a) Using fib2, what is the largest N for which you can compute the 
Nth fibonacci number without getting an error ?
Why does fib2 generate this error?  Is the underlying algorithm incorrect, 
or is their a bug in the implementation?  Explain.

b) What is the largest N for which fib2(N) completes in under a second?
By a back-of-the-envelope calculation, estimate roughly what the largest N would
be for which fib2(N) would complete in under a day.

c) Is the running time of fib2(N) polynomial in N?  Explain.

(If you get seg-faults or times = zero with fib2, you can use fib3 instead.)

To get credit for the lab assignment, prepare answers to these questions 
in the file solutions.txt, or in a pdf file called solutions.pdf, then submit 
the file to the ilearn turn in for lab 1 by TUESDAY, April 10.

In the file you submit, please put the following information:


---------------------------------------------------------------------
name:
sid:
email:
name of lab partner, if any:
---------------------------------------------------------------------
any feedback or questions:

---------------------------------------------------------------------
ANSWERS TO 1:
a)
b)
c)

ANSWERS TO 2:
a)
b)
c)
---------------------------------------------------------------------

#Names: Jeffrey Shaw, David Klien
#Login: shawj, kliend
#Email: shawj@cs.ucr.edu, kliend@cs.ucr.edu
#Lab Section: 022
#Assignment: Lab #2
#I acknowledge all content is original.


#-----------------------------------------------------------
#
#Instructions:
# inputs: A, B
#	input A -> location of binary point from the right
#	 example: 0100 00100 0000 location = 7 for 8.25
#
#	input B -> number to convert to float
#	 example: 8.25
#
#-----------------------------------------------------------


.text
.globl main

main:
	subu $sp, $sp, 32 
	sw $ra, 20($sp)
	sw $fp, 16($sp)
	addiu $fp, $sp, 28

#User Interface


#Print "Running Fixed Point to Float Point Application"


li $v0,4
la $a0, STR1		#Print "Enter L: "
syscall

li $v0,5
syscall

add $s0, $v0, $zero	#s0 -> location of binary point
add $a0, $v0, $zero
li $v0, 1
syscall

li $v0,4
la $a0, STR2		#Print "Enter fixed-point: "
syscall

li $v0,5
syscall

add $s1, $v0, $zero 	#s1 -> fixed point number
add $a0, $v0, $zero
li $v0, 1
syscall

bge $s1, $zero, positive

#negative	convert to positive
nor $s1, $s1, $s1
add $s1, $s1, 1

#need to store negative bit as msb of float
add $s3, $zero, 1

positive:

add $s4, $s1, $zero
lw $t0, var1				# $t0 = 32 this is our counter
add $t4, $zero, $zero			# $t4 is incrimentor

la $t1, array1				# load base address of array into register $t1
li $t2, 0				# $t2 = 0 (load immidiate)
li $t3, 1				# $t3 = 1 (load immidiate)
li $t6, 0x80000000


#_______________________________________
li $v0,4
la $a0, STR3		
syscall
#_______________________________________


bit_check_loop:

and $t7, $s4, $t6
bge $t7, $zero, add_zero		# branch (positive) >= 0 to add a zero to array
blt $t7, $zero, add_one			# branch (negative) < 0 to add a one to array

add_zero:

add $t5, $t1, $t4			# store base + offset
sw $t2, 0($t5)				# add 0 to array
addi $t4, $t4, 4			# incriment incrimentor
addi $t0, $t0, -1			# decriment counter
sll $s4, $s4, 1				# left shift
bgt $t0, $zero, bit_check_loop		# if counter > 0 continue loop
ble $t0, $zero, bit_done		# if counter <= 0 finished loop 

add_one:

add $t5, $t1, $t4			# store base + offset
sw $t3, 0($t5)				# add 1 to array
addi $t4, $t4, 4			# incriment incrimentor
addi $t0, $t0, -1			# decriment counter
sll $s4, $s4, 1				# left shift
bgt $t0, $zero, bit_check_loop		# if counter > 0 continue loop
ble $t0, $zero, bit_done		# if counter <= 0 finished loop 

bit_done:

#------------------PRINT LOOP------------------#
add $t4, $zero, $zero
addi $t0, $zero, 32

li $v0,4
la $a0, STR4		
syscall

Print_Loop:

add $t5, $t1, $t4
lw $t2, 0($t5)
li $v0, 1
move $a0, $t2
syscall
addi $t4, $t4, 4
addi $t0, $t0, -1
bgt $t0, $zero, Print_Loop
#----------------END PRINT LOOP----------------#

#--------------FIND FIRST BIT LOOP-------------#
add $t4, $zero, $zero
add $t0, $zero, $zero

find_first_bit_loop:
add $t5, $t1, $t4			# store base + offset
lw $t2, 0($t5)
addi $t4, $t4, 4
addi $t0, $t0, 1
addi $t2, $t2, -1
bne $t2, $zero, find_first_bit_loop
#-----------END FIND FIRST BIT LOOP------------#

li $v0,4
la $a0, STR6		
syscall

addi $t0, $t0, -1
li $t7, 0
li $t6, 4
mult $t0, $t6
mflo	$t6
add $t4, $t1, $t6
sw $t7, 0($t4)

addi $t0, $t0, 1
add $s5, $t0, $zero		# s0 <- t0

#--------------CALCULATE EXPONENT--------------#
addi $t2, $zero, 32		# t2 <- 32
add $t0, $t0, $s0		# t0 <- t0 + s0
sub $t0 $t2, $t0		# t0 <- t2 - t0
lw $t2, var2			# t2 <- 127
add $t0, $t0, $t2		# t0 <- t0 + 127
add $s0, $t0, $zero		# s0 <- t0
#------------END CALCULATE EXPONENT------------#

#-----------------CREATE ARRAY2----------------#
la $t1, array2				# load address of array2 into $t2
lw $t0, var1				# $t0 = 32 this is our counter
add $t4, $zero, $zero			# $t4 is incrimentor
li $t2, 0				# $t2 = 0 (load immidiate)
li $t3, 1				# $t3 = 1 (load immidiate)
li $t6, 0x80000000

bit_check_loop2:

and $t7, $s0, $t6
bge $t7, $zero, add_zero2		# branch (positive) >= 0 to add a zero to array
blt $t7, $zero, add_one2		# branch (negative) < 0 to add a one to 

add_zero2:

add $t5, $t1, $t4			# store base + offset
sw $t2, 0($t5)				# add 0 to array
addi $t4, $t4, 4			# incriment incrimentor
addi $t0, $t0, -1			# decriment counter
sll $s0, $s0, 1				# left shift
bgt $t0, $zero, bit_check_loop2		# if counter > 0 continue loop
ble $t0, $zero, bit_done2		# if counter <= 0 finished loop 

add_one2:

add $t5, $t1, $t4			# store base + offset
sw $t3, 0($t5)				# add 1 to array
addi $t4, $t4, 4			# incriment incrimentor
addi $t0, $t0, -1			# decriment counter
sll $s0, $s0, 1				# left shift
bgt $t0, $zero, bit_check_loop2		# if counter > 0 continue loop
ble $t0, $zero, bit_done2		# if counter <= 0 finished loop 

bit_done2:
#---------------END CREATE ARRAY2----------------#

#-----------------CREATE ARRAY3------------------#
addi $t4, $zero, 4

la $t1, array2
la $t2, array3

li $t7, 23
mult $t7, $t4
mflo $t7

add $t1, $t1, $t7
li $t6, 9
array3_loop:
lw $t5, 0($t1)
sw $t5, 0($t2)
add $t1, $t1, $t4
add $t2, $t2, $t4
addi $t6, $t6, -1
bne $t6, $zero, array3_loop
#---------------END CREATE ARRAY3----------------#

#---------------CREATE ARRAY3 PART2--------------#
addi $t4, $zero, 4

la $t1, array1
la $t2, array3
addi $s5, $s5, -1

mult $s5, $t4
mflo $t7
add $t1, $t1, $t7

li $t6, 8
mult $t6, $t4
mflo $t7
add $t2, $t2, $t7

li $t6, 32				# t6 is our counter
sub $t6, $t6, $s5

array3_loop2:
lw $t5, 0($t1)
sw $t5, 0($t2)
add $t1, $t1, $t4
add $t2, $t2, $t4
addi $t6, $t6, -1
bne $t6, $zero, array3_loop2
#----------END CREATE ARRAY3 PART2-------------#

#------------------PRINT LOOP------------------#
add $t4, $zero, $zero
addi $t0, $zero, 32
la $t1, array3

li $v0,4
la $a0, STR4		
syscall

Print_Loop2:

add $t5, $t1, $t4
lw $t2, 0($t5)
li $v0, 1
move $a0, $t2
syscall
addi $t4, $t4, 4
addi $t0, $t0, -1
bgt $t0, $zero, Print_Loop2
#----------------END PRINT LOOP----------------#

li $v0,4
la $a0, STR6		
syscall

beq $s3, $zero, calc_num		# this will add the msb if our original 
la $t1, array3				#	number is negative
sw $s3, 0($t1)

#------------------PRINT LOOP------------------#
add $t4, $zero, $zero
addi $t0, $zero, 32
la $t1, array3

li $v0,4
la $a0, STR4		
syscall

Print_Loop3:

add $t5, $t1, $t4
lw $t2, 0($t5)
li $v0, 1
move $a0, $t2
syscall
addi $t4, $t4, 4
addi $t0, $t0, -1
bgt $t0, $zero, Print_Loop3
#----------------END PRINT LOOP----------------#

li $v0,4
la $a0, STR6		
syscall

#-------------CALCULATE FINAL NUMBER-----------#
calc_num:
la $t1, array3
li $t2, 32
add $s5, $zero, $zero
addi $t4, $zero, 4
addi $t6, $zero, 1

mult $t2, $t4
mflo $t2

add $t3, $t1, $t2
addi $t3, $t3, -4
li $t5, 32

calc_loop:
lw $t0, 0($t3)
bne $t0, $zero, do_add
add $t6, $t6, $t6
addi $t3, $t3, -4
addi $t5, $t5, -1
bge $t5, $zero, calc_loop

j finish

do_add:
add $s5, $s5, $t6
add $t6, $t6, $t6
addi $t3, $t3, -4
addi $t5, $t5, -1
bne $t5, $zero, calc_loop
#----------END CALCULATE FINAL NUMBER-----------#

finish:

li $v0,4
la $a0, STR6		
syscall

li $v0, 1
move $a0, $s5
syscall

li $v0,4
la $a0, STR5		
syscall

DONE:

.data

array1:		.space	128	# set array size to hold 32 integers
array2:		.space	128	# set array size to hold 32 integers
array3:		.space	128	# set array size to hold 32 integers
var1:		.word	32
var2:		.word	127

STR1:
	.asciiz "Enter L: "

STR2:
	.asciiz "Enter fixed-point: "

STR3:
	.asciiz "\ncomputing binary number\n"

STR4:
	.asciiz "printing binary number\n"

STR5:
	.asciiz "\nEND\n"

STR6:
	.asciiz "\n"

STR7:
	.asciiz "Adding One\n"

STR8:
	.asciiz "Adding Zero\n"
STR9:
	.asciiz "Number is negative!\n"

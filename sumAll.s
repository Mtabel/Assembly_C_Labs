.data
prompt: .asciiz "Please enter a number:"
EvenPrompt: .asciiz "Sum of even numbers is: "
OddPrompt: .asciiz "Sum of Odd numbers is: "

newline: .asciiz "\n"

#$t3 is even sums
#$t4 is odd sums

.text

#loop start
start:

	# ask user for input
	li $v0, 4 # Syscall 4 = print string
	la $a0, prompt # loads address $a0 with prompt data
	syscall #issues call to system to print register $a0	
	
	#get int input
	li $v0, 5 # loading instruction to read integer into the system
	syscall
	move $t0, $v0 #saves the input assigned to $v0 to $t0
	
	#Check Whether is zero - if so branch off
	beq $t0, $zero, finish
	
	
	#check whether if even or odd by bit shift
	srl $t1, $t0, 1
	sll $t1, $t1, 1
	bne $t0, $t1, Odd
	# even Code Down here
	add $t4, $t4, $t0
	j start

Odd:	
	add $t3, $t3, $t0
	# Repeat at top -- 
	j start
	
finish: 
	#print even and odd scores
	li $v0, 4 # Syscall 4 = print string
	la $a0, EvenPrompt # loads address $a0 with prompt data
	syscall
	#print associated Integer
	li $v0, 1 # Syscall 4 = print string
	move $a0, $t3 # loads address $a0 with prompt data
	syscall #issues call to system to print register $a0	
	
	li $v0, 4 # Syscall 4 = print string
	la $a0, newline # loads address $a0 with prompt data
	syscall
	
	#print even and odd scores
	li $v0, 4 # Syscall 4 = print string
	la $a0, OddPrompt # loads address $a0 with prompt data
	syscall
	
	#print associated Integer
	li $v0, 1 # Syscall 4 = print string
	move $a0, $t4 # loads address $a0 with prompt data
	syscall #issues call to system to print register $a0	
	
	
	
	
	li $v0, 10 # Load a 10 (service number for halt) into $v0.
	syscall # The program ends because syscall reads the value of 10 in $v0.
	
	
	
	
	
#
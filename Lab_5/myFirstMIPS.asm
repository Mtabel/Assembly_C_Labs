.data	# Define the program data (static data segment).
prompt: .asciiz "Enter a number: " # Define UserPrompt

newline: .asciiz "\n"	     

.text	# Define the program instructions (text segment).
	
	
	li $v0, 4 # Syscall 4 = print string
	la $a0, prompt # loads address $a0 with prompt data
	syscall #issues call to system to print register $a0
	
	#Read integer
	li $v0, 5 # loading instruction to read integer into the system
	syscall
	
	#Store result into $t0
	move $s0, $v0 #saves the input assigned to $v0 to $t0
	
	
	#$t0 = $s0 
	move $t0, $s0
	#$t1 = $t0 - 7
	addi $t1, $t0, -7
	#$t2 = $t1 + $t0
	add $t2, $t1, $t0
	#$t3 = $t2 + 2
	addi $t3, $t2, 2
	#$t4 = $t3 + $t2
	add $t4, $t3, $t2
	#$t5 = $t4 - 28
	addi $t5, $t4, -28
	#$t6 = $t4 - $t5
	sub $t6, $t4, $t5
	#$t7 = $t6 + 12
	addi $t7, $t6, 12
	
	
	move $a0, $t7
	li $v0, 1
	syscall
	
	li $v0, 10 # Load a 10 (service number for halt) into $v0.
	syscall # The program ends because syscall reads the value of 10 in $v0.

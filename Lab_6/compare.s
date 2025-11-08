.data

prompt: .asciiz "Give an integer: "

str1: .asciiz "Less than\n"
str2: .asciiz "Less than or equal to\n"
str3: .asciiz "Greater than\n"
str4: .asciiz "Greater than or equal to\n"

n: .word 10

.text
	la $t1, n
	lw $t1, 0($t1)
	
	#Print Prompt
	li $v0, 4 # Syscall 4 = print string
	la $a0, prompt # loads address $a0 with prompt data
	syscall #issues call to system to print register $a0	
	
	#Read integer
	li $v0, 5 # loading instruction to read integer into the system
	syscall
	
	#Store result into $t0
	move $s0, $v0 #saves the input assigned to $v0 to $t0
	
#-------------------------------------------------
		#Complete Less Than
	#slt $t0, $s0, $t1 
	#bne $t0, $zero, LT

		#Complete Greater than or equal to
	#slt $t0, $s0, $t1 
	#beq $t0, $zero, GE
	#j finish
	#Comment out above ------------------------
	#Make only greater than
	slt $t0, $t1, $s0
	bne $t0, $zero, GT
	#Make Less than equal
	slt $t0, $t1, $s0
	beq $t0, $zero, LTE
	j finish
	
LT: #Less Than
	li $v0, 4 # Syscall 4 = print string
	la $a0, str1 # loads address $a0 with prompt data
	syscall
	addi $t4, $t4, 1	
	j finish
GE: #Greater than or Equal to
	li $v0, 4 # Syscall 4 = print string
	la $a0, str4 # loads address $a0 with prompt data
	syscall
	addi $t4, $t4, 2
	j finish
EQ: #Equal to
	addi $t4, $t4, 3
	j finish
NE: #Not Equal
	addi $t4, $t4, 4
	j finish
GT:
	li $v0, 4 # Syscall 4 = print string
	la $a0, str3 # loads address $a0 with prompt data
	syscall
	addi $t4, $t4, 5
	j finish

LTE:
	li $v0, 4 # Syscall 4 = print string
	la $a0, str2 # loads address $a0 with prompt data
	syscall
	addi $t4, $t4, 6
	j finish
	
finish:
	li $v0, 10 # Load a 10 (service number for halt) into $v0.
	syscall # The program ends because syscall reads the value of 10 in $v0.
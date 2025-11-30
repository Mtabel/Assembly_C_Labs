.data
n:      .word 13
prompt: .asciiz "Please enter a number: "

.text
main: 	
	li $v0, 4 # Load write command
	la $a0, prompt #Load Prompt into argument
	syscall # Execute
	
	li $v0, 5 #Ask for User Input
	syscall
	
	
	
	
	
	add     $t0, $0, $zero
	addi    $t1, $zero, 1
	add     $t3, $t3, $v0
		
fib: 	beq     $t3, $0, finish
	add     $t2,$t1,$t0
	move    $t0, $t1
	move    $t1, $t2
	subi    $t3, $t3, 1
	j       fib
		
finish: addi    $a0, $t0, 0
	li      $v0, 1		
	syscall			
	li      $v0, 10		
	syscall			


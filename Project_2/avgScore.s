.data 

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded down) with dropped scores removed: "
space: .asciiz " "
newline: .asciiz "\n"

.text 

# This is the main program.
# It first asks user to enter the number of assignments.
# It then asks user to input the scores, one at a time.
# It then calls selSort to perform selection sort.
# It then calls printArray twice to print out contents of the original and sorted scores.
# It then asks user to enter the number of (lowest) scores to drop.
# It then calls calcSum on the sorted array with the adjusted length (to account for dropped scores).
# It then prints out average score with the specified number of (lowest) scores dropped from the calculation.
main: 
	addi $sp, $sp -4
	sw $ra, 0($sp)
	la $a0, str0 
	li $v0, 4 
	syscall 
	li $v0, 5	# Read the number of scores from user
	syscall
	
	# Your code here to handle invalid number of scores (can't be less than 1 or greater than 25)
	
	move $s0, $v0	# $s0 = numScores
	move $t0, $0
	la $s1, orig	# $s1 = orig
	la $s2, sorted	# $s2 = sorted
loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	# Read elements from user
	syscall
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in
	
	move $a0, $s0
	jal selSort	# Call selSort to perform selection sort in original array
	
	li $v0, 4 
	la $a0, str2 
	syscall
	move $a0, $s1	# More efficient than la $a0, orig
	move $a1, $s0
	jal printArray	# Print original scores
	li $v0, 4 
	la $a0, str3 
	syscall 
	move $a0, $s2	# More efficient than la $a0, sorted
	jal printArray	# Print sorted scores
	
	li $v0, 4 
	la $a0, str4 
	syscall 
	li $v0, 5	# Read the number of (lowest) scores to drop
	syscall
	
	# Your code here to handle invalid number of (lowest) scores to drop (can't be less than 0, or 
	# greater than the number of scores). Also, handle the case when number of (lowest) scores to drop 
	# equals the number of scores. 
	
	move $a1, $v0
	sub $a1, $s0, $a1	# numScores - drop
	move $a0, $s2 
	jal calcSum	# Call calcSum to RECURSIVELY compute the sum of scores that are not dropped
	
	# Your code here to compute average and print it (you may also end up having some code here to help 
	#-------------For Testing Only--------------------
	#print sum for now
	move $a0, $v0
	#print number
	li $v0, 1 #load read command
	#lw $a0, 0($t0)
	syscall #read arg0
	#--------------------------------
	# handle the case when number of (lowest) scores to drop equals the number of scores
	
end:	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10 
	syscall
	
	
# printList takes in an array and its size as arguments. 
# It prints all the elements in one line with a newline at the end.
printArray:

	# Your implementation of printList here	
	#arg one is array
	#arg two is size
	li $t0, 0
	
	move $t0, $a0#address of array
	move $t4, $t0#Keep carbon Copy of array
	move $t1, $a1#elements in array
	li $t2, 0 #acts as i to track for loop
printArray_inner:
	#do the work
	
	#print space
	li $v0, 4 #load read string command
	la $a0, space #load string to print
	syscall #execute string
	
	#print number
	li $v0, 1 #load read command
	lw $a0, 0($t0)
	syscall #read arg0
	addi $t0, $t0, 4 #offset temp array by four to read next
	addi $t2, $t2, 1 # count times process has be done
	
	slt $t3, $t2, $t1 #check if i<arraysize
	bne $t3, $zero, printArray_inner #branch back to loop if ^
	#else ET go home
	
	#print newline
	li $v0, 4 #load read string command
	la $a0, newline #load string to print
	syscall #execute string
	
	
	jr $ra
	
	
# selSort takes in the number of scores as argument. 
# It performs SELECTION sort in descending order and populates the sorted array
selSort:
	# Your implementation of selSort here
	move $t6, $s1 # $s1 = original move to $t7
	move $t7, $s2# $s2 = sorted move to $t8
	
	#Label Temps to desired variables
	#i = $t0
	#j = $t1
	#temp = $t2
	move $t3, $s0#Max Index = $s0 move it to $t3
	
	#for (int i = 0; i < len; ++i)
	li $t0, 0
setloop:

	lw $t5, 0($t6) # load value requested to copy over
	sw $t5, 0($t7) # store loaded value into requested location
	
	addi $t6, $t6, 4 #increment temp address
	addi $t7, $t7, 4 #increment temp address
	
	

	addi $t0, $t0, 1
	slt $t4, $t0, $t3
	bne $t4, $zero, setloop
	#branch back to loop if i < max
	#set elements
	

firstloop:

secondloop:

	

	
	
	
	
	# Reset all temps at end
	jr $ra
	
	
# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
# Note: you MUST NOT use iterative approach in this function.
calcSum: # Your implementation of calcSum here
	#arg 0 is array
	#arg 1 is len
	#prolog
	addi $sp, $sp, -8 #add space on stack for whats to come
	sw $ra, 4($sp) #store return address on top of stack so ET can go home
	sw $a1, 0($sp) #store len for future
	#prolog fin-----
	
	

	
	
#Base Case check
	#if length is less then or equal to 0 just jr $ra
	slt $t0, $a1, $zero
	bne $t0, $zero, basecase
	#else cont.
	
	#Recursive call seg
	addi $a1, $a1, -1#reduce length by 1
	jal calcSum#jump to call and return
	lw $a1, 0($sp)#restore the length
	lw $ra, 4($sp)#restore return address
	
	
	#epi log ----
	sll $t0, $a1, 2 #mutiply len-1 by 4 to get size in memory
	add $t1, $a0, $t0 #add len-1 to address of arr[len-1] to get location of last element in array
	lw $t2, 0($t1) #load the element of that location and hold it temporarily
	add $v0, $v0, $t2#add it to the recursive sum, in this case $v0 which will pass down to each recursive call like the tithe bowl at church.
	
	addi $sp, $sp, 8#Reset stack frame
	#epi finish ----- 
	
	
	jr $ra #jump ship back to main function
basecase:
	#base case reached of len <= 0
	li $v0, 0#return 0
	addi $sp, $sp, 8#set back stack
	jr $ra #return to home
	
	

.data 

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded down) with dropped scores removed: "
str6: .asciiz "All scores dropped!"
#Bonus string
str_drop: .asciiz "Dropped scores: "
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
	slti $t0, $v0, 1      #if less or equal to 0
	bne  $t0, $zero, main

	li $t1, 25
	slt $t0, $t1, $v0 #more than num of scores logic
	bne $t0, $zero, main
	
	
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
	move $a1, $s0
	jal printArray	# Print sorted scores
	
comeback:
	li $v0, 4 
	la $a0, str4 
	syscall 
	li $v0, 5	# Read the number of (lowest) scores to drop
	syscall
	
	# Your code here to handle invalid number of (lowest) scores to drop (can't be less than 0, or 
	# greater than the number of scores). Also, handle the case when number of (lowest) scores to drop 
	# equals the number of scores.
	
	 
	slt $t0, $v0, $zero   #less than logic zero logic
	bne $t0, $zero, comeback

	slt $t0, $s0, $v0 #more than num of scores logic
	bne $t0, $zero, comeback
	
	slt $t0, $v0, $s0 #equal logic
	slt $t1, $s0, $v0
	or $t2, $t0, $t1
	beq $t2, $zero, equaldrop
	#End of conditionals
	
	sub $s4, $s0, $v0 #load son up as $s4 for later tampering
	     
	#-------- Leave this guy alone
cont:
	move $a1, $v0
	sub $a1, $s0, $a1	# numScores - drop
	move $a0, $s2 
	jal calcSum	# Call calcSum to RECURSIVELY compute the sum of scores that are not dropped
	move $s5, $v0
	# Your code here to compute average and print it (you may also end up having some code here to help 
	
	#Bonus part
	# print "Dropped scores: "
	li $v0, 4	# syscall 4 = print string
	la $a0, str_drop	# load address of "Dropped scores: "
	syscall		 # print it
	
	#number dropped = s0 - s4
	sub $t2, $s0, $s4	# t2 = numberDropped = totalScores - numberKept
	
	#address of first dropped element in sorted array
	sll $t4, $s4, 2		# t4 = numberKept * 4 (byte offset)
	add $t3, $s2, $t4	 # t3 = &sorted[numberKept] (start of dropped scores)
	
	li $t5, 0	# t5 = loop counter = 0
drop_loop:
	beq $t5, $t2, drop_done		# if counter == numberDropped → exit loop
	
	#print space
	li $v0, 4	# syscall 4 = print string
	la $a0, space	# space = " "
	syscall		# print space
	
	#print dropped value
	li $v0, 1	# syscall 1 = print integer
	lw $a0, 0($t3)	# load dropped score into $a0
	syscall		# print the integer

	
	addi $t3, $t3, 4	 # move to next dropped score (advance by 4 bytes)
	addi $t5, $t5, 1	# increment loop counter
	j drop_loop	# repeat loop

drop_done:
	# print newline
	li $v0, 4	# syscall 4 = print string
	la $a0, newline	# load newline ("\n")
	syscall		# print newline
	
	#End of bonus
	
	#print string
	li $v0, 4 #load command write string
	la $a0, str5 # load string
	syscall #fire
	
	div $s5, $s4
	mflo $a0 #laod final answer
	li $v0, 1 #load command write int
	syscall 
	
	
	# handle the case when number of (lowest) scores to drop equals the number of scores
	
end:	
	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10 
	syscall
	
equaldrop:
#say that shit equals through syscal then end program

li $v0, 4 #load command write string
la $a0, str6 # load string
syscall #fire
j end #swish	
		
#end--------	
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
	move $t3, $s0#len = $s0 move it to $t3
	
	
	#for (int i = 0; i < len; ++i)
	li $t0, 0
setloop:

	lw $t5, 0($t6) # load value requested to copy over
	sw $t5, 0($t7) # store loaded value into requested location
	
	addi $t6, $t6, 4 #increment temp address
	addi $t7, $t7, 4 #increment temp address
	
	

	addi $t0, $t0, 1
	slt $t4, $t0, $t3 # if less set $t4 to 1
	bne $t4, $zero, setloop #if less; branch
	#branch back to loop if i < max
	#set elements
	
	li $t6, 0 #reset temps to make it look good at break points
	li $t7, 0 #clean up^
	
	

	li $t0, 0 #i = $t0
	li $t1, 0 #j = $t1
	#temp = 	     $t2
	#len = $s0 or  $t3
	#max val index $t4
	move $t5, $s2# $s2 = sorted move to $t5
	#move $s3, $s2# store copy for moving through
firstloop:#i zero at start
	#I's for loop
	
	move $t4, $t0#max = i
	
	addi $t1, $t0, 1
secondloop: #J's for loop
	
	#find offset for array needed
	sll $t6, $t1, 2#----Multiply j by 4
	add $t6, $t6, $s2#----add value found to copy
	lw $s3, 0($t6) #save value into save register
	#load j val
	sll $t6, $t4, 2#----Multiply j by 4
	add $t6, $t6, $s2#----add value found to copy
	lw $s4, 0($t6) #save value into save register
	
	#we have j and max: now we need to run logic
	#if sorted j val > sorted max val else pass
	slt $t6, $s4, $s3
	beq $t6, $zero, pass
	move $t4, $t1 #max = j
	
pass:
	
	addi $t1, $t1, 1
	subi $t7, $t3, 1#$t7 = len - 1
	#secondloop conditional release
	slt $t6, $t1, $t3
	bne $t6, $zero, secondloop
	
	#temp = sorted[maxIndex
	sll $t6, $t4, 2#----Multiply max by 4
	add $t6, $t6, $s2#----add value found to copy
	move $t7, $t6 #address of max ----<>
	lw $s3, 0($t6) #save value into save register
	move $t2, $s3
	#sorted[max] = sorted[i
	sll $t6, $t0, 2#----Multiply i by 4
	add $t6, $t6, $s2#----add value found to copy
	move $t8, $t6 #save address of sort i ----<>
	lw $s4, 0($t6) #save value into save register
	sw $s4, 0($t7) #completed step
	#sorted[i = temp
	sw $t2, 0($t8)
	
	
	
	addi $t0, $t0, 1
	#first loop conditional release
	slt $t6, $t0, $t3
	bne $t6, $zero, firstloop
	# Reset all temps at end
	li $s3, 0 #reset regs
	li $s4, 0 #reset regs
	
	#reset all temps since it makes it clean:
	li $t0, 0
	li $t1, 0
	li $t2, 0
	li $t3, 0
	li $t4, 0
	li $t5, 0
	li $t6, 0
	li $t7, 0
	li $t8, 0
	li $t9, 0
	
	jr $ra # GTFO
	
	
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
	addi $t0, $a1, -1   # len - 1
	sll  $t0, $t0, 2 #mutiply len-1 by 4 to get size in memory
	#sll $t0, $a1, 2 #mutiply len-1 by 4 to get size in memory
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
	
	

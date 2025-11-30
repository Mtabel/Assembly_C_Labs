.data

# TPS 2 #3 (input prompt to be displayed)
str1: .asciiz "Please enter a number: "

.text
main:
    # TPS 2 #3 (display input prompt)
    la $a0, str1
    li $v0, 4
    syscall

    addi $sp, $sp, -4   # Make space for saved x

    # TPS 2 #4 (read user input)
    li $v0, 5
    syscall
    sw $v0, 0($sp)      # Save x on stack
    move $a0, $v0       # Pass x into recursion()

    jal recursion       # Call recursion(x)

    # TPS 2 #6 (print out returned value)
    move $a0, $v0
    li $v0, 1
    syscall

    j end               # Exit program


# recursion(m)

recursion:
    addi $sp, $sp, -12  # Push stack frame for this call

    # TPS 2 #7
    sw $ra, 8($sp)      # Save return address
    sw $a0, 4($sp)      # Save m

    # if (m == -1)
    lw $t0, 4($sp)
    li $t1, -1
    beq $t0, $t1, base_minus_one

    # if (m == 0)
    li $t1, 0
    beq $t0, $t1, base_zero


#Recursive Case
# TPS 2 #11 (Prepare new input argument, m - 2)
    addi $a0, $t0, -2
    jal recursion       # recursion(m - 2)

    # TPS 2 #12
    sw $v0, 0($sp)      # Save recursion(m - 2)

# TPS 2 #13 (Prepare new input argument, m - 1)
    lw $a0, 4($sp)
    addi $a0, $a0, -1
    jal recursion       # recursion(m - 1)

# TPS 2 #14 (update returned value)
    lw $t1, 0($sp)
    addu $v0, $v0, $t1  # v0 = rec(m-1) + rec(m-2)
    j end_recur


#Base Cases
base_minus_one:
    # TPS 2 #8
    li $v0, 1           # return 1
    j end_recur

base_zero:
    # TPS 2 #9
    li $v0, 3           # return 3
    j end_recur



# End recursion() — restore frame and return

end_recur:
    lw $ra, 8($sp)
    addi $sp, $sp, 12
    jr $ra



# Program exit
end:
    addi $sp, $sp, 4     # Pop x off stack
    li $v0, 10
    syscall

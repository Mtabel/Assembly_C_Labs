.data
str1: .asciiz "Please enter a number: "

.text
main:
    addi $sp, $sp, -4        # allocate space
    move $s1, $sp

    # print prompt
    la $a0, str1
    li $v0, 4
    syscall

    # read int
    li $v0, 5
    syscall
    move $a0, $v0           # pass input to recursion

    jal recursion           # call recursion(x)

    # print returned value
    move $a0, $v0
    li $v0, 1
    syscall

    j end


# recursion(m)
recursion:
    addi $sp, $sp, -12      # stack frame
    sw $ra, 8($sp)          # save return address
    sw $a0, 4($sp)          # save m

    lw  $t0, 4($sp)         # t0 = m

    # Base case: m == -1  ? return 1
    li $t1, -1
    beq $t0, $t1, base_minus_one

    # Base case: m == 0 ? return 3
    li $t1, 0
    beq $t0, $t1, base_zero


    # Recursive case: rec(m-2) + rec(m-1)

    # ---- First call: recursion(m - 2) ----
    addi $a0, $t0, -2
    jal recursion
    sw $v0, 0($sp)          # save rec(m-2)

    # ---- Second call: recursion(m - 1) ----
    lw $a0, 4($sp)          # restore original m
    addi $a0, $a0, -1
    jal recursion

    # combine results
    lw $t1, 0($sp)          # rec(m-2)
    addu $v0, $v0, $t1      # v0 = rec(m-1) + rec(m-2)
    j end_recur


# Base return values
base_minus_one:
    li $v0, 1
    j end_recur

base_zero:
    li $v0, 3
    j end_recur


# function epilogue
end_recur:
    lw $ra, 8($sp)
    addi $sp, $sp, 12
    jr $ra


# End of program
end:
    addi $sp, $sp, 4
    li $v0, 10
    syscall

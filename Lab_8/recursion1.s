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


recursion:
    addi $sp, $sp, -16         # create stack frame
    sw $ra, 12($sp)            # save return address
    sw $a0, 8($sp)             # save argument m

    lw $t0, 8($sp)             # load m into t0

    li $t1, -1                 # check m == -1
    beq $t0, $t1, base_minus_one

    li $t1, -2                 # check m == -2
    beq $t0, $t1, base_minus_two

    li $t1, -2                 # if m < -2
    blt $t0, $t1, base_less_than_minus_two


    # recursive case: rec(m-3)
    addi $a0, $t0, -3          # prepare argument m-3
    jal recursion              # call recursion(m-3)
    sw $v0, 4($sp)             # save rec(m-3)


    #recursive case: rec(m-2)
    lw $a0, 8($sp)             # restore original m
    addi $a0, $a0, -2          # compute m-2
    jal recursion              # call recursion(m-2)

    # combine: rec(m-3) + m + rec(m-2)
    lw $t1, 4($sp)             # rec(m-3)
    lw $t2, 8($sp)             # m
    addu $v0, $v0, $t1         # rec(m-2) + rec(m-3)
    addu $v0, $v0, $t2         # + m
    j end_recur


#base cases
base_minus_one:
    li $v0, 3                  # return 3
    j end_recur

base_minus_two:
    li $v0, 1                  # return 1
    j end_recur

base_less_than_minus_two:
    li $v0, 2                  # return 2
    j end_recur


# end recursion
end_recur:
    lw $ra, 12($sp)            # restore return address
    addi $sp, $sp, 16          # destroy stack frame
    jr $ra                     # return to caller

# End of program
end:
    addi $sp, $sp, 4
    li $v0, 10
    syscall

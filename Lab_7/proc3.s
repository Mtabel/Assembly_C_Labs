# proc3_mars_fixed.s
.data
msg_pq:    .asciiz "p + q: "
newline:   .asciiz "\n"

.text
.globl MAIN

# -------------------------
# MAIN
# -------------------------
MAIN:
    # map locals: x -> $s0, y -> $s1, z -> $s2
    li   $s0, 2        # x = 2
    li   $s1, 4        # y = 4
    li   $s2, 6        # z = 6

    # call foo(x,y,z)
    move $a0, $s0      # m = x
    move $a1, $s1      # n = y
    move $a2, $s2      # o = z
    jal  FOO

    # z = x + y + z + foo(...)
    addu $s2, $s2, $v0
    addu $s2, $s2, $s0
    addu $s2, $s2, $s1

    # print final z (integer) and newline
    move $a0, $s2
    li   $v0, 1
    syscall

    la   $a0, newline
    li   $v0, 4
    syscall

    # exit
    li   $v0, 10
    syscall


# -------------------------
# FOO: int foo(int m,int n,int o)
# locals: p -> $s0, q -> $s1
# Prologue saves: $ra, $s0, $s1, and original $a0,$a1,$a2 on stack
# -------------------------
FOO:
    # allocate stack and save registers (24 bytes)
    addiu $sp, $sp, -24
    sw    $ra, 0($sp)
    sw    $s0, 4($sp)
    sw    $s1, 8($sp)
    sw    $a0, 12($sp)   # save original m
    sw    $a1, 16($sp)   # save original n
    sw    $a2, 20($sp)   # save original o

    # -------- compute p = bar(m+o, n+o, m+n) --------
    lw    $t0, 12($sp)   # t0 = m
    lw    $t1, 16($sp)   # t1 = n
    lw    $t2, 20($sp)   # t2 = o

    addu  $a0, $t0, $t2  # a0 = m + o
    addu  $a1, $t1, $t2  # a1 = n + o
    addu  $a2, $t0, $t1  # a2 = m + n
    jal   BAR
    move  $s0, $v0       # p = v0

    # -------- compute q = bar(m-o, n-m, n+n) --------
    # reload originals
    lw    $t0, 12($sp)   # t0 = m
    lw    $t1, 16($sp)   # t1 = n
    lw    $t2, 20($sp)   # t2 = o

    subu  $a0, $t0, $t2  # a0 = m - o
    subu  $a1, $t1, $t0  # a1 = n - m
    addu  $a2, $t1, $t1  # a2 = n + n
    jal   BAR
    move  $s1, $v0       # q = v0

    # -------- compute p + q in a temp and print "p + q: <val>" --------
    addu  $t3, $s0, $s1  # t3 = p + q (use $t3 to preserve value across syscalls)

    # print "p + q: "
    la    $a0, msg_pq
    li    $v0, 4
    syscall

    # print integer (p + q): move t3 -> a0, set v0=1
    move  $a0, $t3
    li    $v0, 1
    syscall

    # print newline
    la    $a0, newline
    li    $v0, 4
    syscall

    # place return value in $v0 = p + q
    move  $v0, $t3

    # -------- epilogue: restore and return p+q in $v0 ----------
    lw    $ra, 0($sp)
    lw    $s0, 4($sp)
    lw    $s1, 8($sp)
    addiu $sp, $sp, 24
    jr    $ra


# -------------------------
# BAR: int bar(int a,int b,int c)
# returns (b - a) << c  (shift left by c bits)
# Inputs: a -> $a0, b -> $a1, c -> $a2
# Returns: value in $v0
# -------------------------
BAR:
    # compute b - a
    subu  $t0, $a1, $a0   # t0 = b - a

    # variable shift left by c: sllv rd, rt, rs  => rd = rt << (rs & 0x1F)
    sllv  $v0, $t0, $a2   # v0 = (b - a) << c

    jr    $ra

.globl main

.data
source:
    .word   3
    .word   1
    .word   4
    .word   1
    .word   5
    .word   9
    .word   0
dest:
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0

.text
fun:
    addi t0, a0, 1
    sub t1, x0, a0
    mul a0, t0, t1
    jr ra

main:
    # BEGIN PROLOGUE
    addi sp, sp, -20
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw ra, 16(sp)
    # END PROLOGUE
    addi t0, x0, 0 # t0 = k
    addi s0, x0, 0
    la s1, source
    la s2, dest # s2 = dest array
loop:

    # first line of the for loop
    slli s3, t0, 2 # move pointer, t0 = k
    add t1, s1, s3 # t1: address of the source at k / move the pointer to source by s3
    lw t2, 0(t1) # load the element from the source
    beq t2, x0, exit # exit if t2(source[k]) == 0

    # second line of for loop (RHS)
    add a0, x0, t2 # a0 = t2 will be the argument to the fun function
    addi sp, sp, -8
    sw t0, 0(sp) # store t0 = k
    sw t2, 4(sp) # store t2 = source[k]
    jal fun # call fun function
    lw t0, 0(sp) # load the stored k value
    lw t2, 4(sp) # load the stored source[k]
    addi sp, sp, 8 # move the stack pointer back up

    # second line of for loop (LHS)
    add t2, x0, a0 # t2 = return value of the fun function
    add t3, s2, s3 # t3 = pointer to the dest array at k
    sw t2, 0(t3) # store t2 at t3
    add s0, s0, t2 # s0 is the sum, add return value of the fun function to the sum
    addi t0, t0, 1 #
    jal x0, loop
exit:

    # return sum;
    add a0, x0, s0 # a0 = s0 = sum will be the return value of the main; sum
    
    # BEGIN EPILOGUE
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw ra, 16(sp)
    addi sp, sp, 20
    # END EPILOGUE
    jr ra

/**
 *  la t0, n // t0 = address to where the input is
    lw a0, 0(t0) // a0 is the argument 
    jal ra, factorial

    addi a1, a0, 0 // a0 = output of the factorial function = a1
    addi a0, x0, 1 // 1 will print what is in a1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11 // 11 will print what is in a1
    ecall # Print newline

    addi a0, x0, 10 // 10 will exit
    ecall # Exit
*/

#include <stdio.h>

int factorial(int n) {
    int res = 1;
    while (n >= 1) {
        res = res * n;
        n = n - 1;
    }
    return res;
}

int main() {
    
    printf("%d\n", factorial(6));
}

// s0 = res
// t0 = n
// t1 = 1

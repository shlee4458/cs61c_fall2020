#include <stdio.h>
#include "bit_ops.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // YOUR CODE HERE

    // x AND a bitstring with nth digit with 1 and rest 0
    // later -> leftshift n times 0.....01 = 1
    
    return (x & (1<<n))>>n;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE

    unsigned int nth_x = (*x & (1<<n))>>n;
    // if nth digit of x is same with v do nothing

    // if nth digit is not same as v
    // if x = 1, v = 0 ; subtraction - v or (not x or v)
    // if x = 0, v = 1 ; addition
    if (nth_x == 1 && v == 0) {
        *x = ~(1<<n | ~(*x | 1<<n));
    }

    else if (nth_x == 0 && v == 1) {
        *x = (*x | 1<<n);
    }


    // step 2: change rest of the digits of x to the original
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // YOUR CODE HERE
    *x = (*x^(1<<n));
}


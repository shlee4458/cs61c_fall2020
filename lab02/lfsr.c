#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

int nth_digit(uint16_t bnum, int n) {
    return (bnum&(1<<n))>>n;
}


void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */

    // Compute the number to go into the 15th index
    int ndigit = nth_digit(*reg, 0);
    int ar[3] = {2, 3, 5};
    for (int i = 0; i < 3; i++) {
        ndigit = ndigit ^(nth_digit(*reg, ar[i]));
    }

    // Shift the reg to right by one
    *reg = *reg>>1;

    // Insert the value to the index
    *reg = *reg | ndigit<<15;
}




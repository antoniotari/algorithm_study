//
//  main.c
//  algorithm study c
//
//  Created by Antonio Tari on 6/16/15.
//  Copyright (c) 2015 ___ANTONIO_TARI___. All rights reserved.
//

#include <stdio.h>
#include "PrintPathToLeafs.h"

static const float VALUE = 4.82345435647456;

/*
 * Calculate the square root of a double
 * Quake 3 solution
*/
float fast_sqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
    
    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                     // floating point bit level hacking [sic]
    i  = 0x5f3759df - ( i >> 1 );             // Newton's approximation
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
    y  = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration
    y  = y * ( threehalfs - ( x2 * y * y ) ); // 3rd iteration
    
    return 1/y;
}

/* Assumes that float is in the IEEE 754 single precision floating point format
 * and that int is 32 bits. */
float sqrt_approx(float z){
    int val_int = *(int*)&z; /* Same bits, but as an int */
    /*
     * To justify the following code, prove that
     *
     * ((((val_int / 2^m) - b) / 2) + b) * 2^m = ((val_int - 2^m) / 2) + ((b + 1) / 2) * 2^m)
     *
     * where
     *
     * b = exponent bias
     * m = number of mantissa bits
     *
     * .
     */
    
    val_int -= 1 << 23; /* Subtract 2^m. */
    val_int >>= 1; /* Divide by 2. */
    val_int += 1 << 29; /* Add ((b + 1) / 2) * 2^m. */
    //val_int = (1 << 29) + (val_int >> 1) - (1 << 22) + a;
    return *(float*)&val_int; /* Interpret again as float */
}



int main(int argc, const char * argv[]) {
    float squa = fast_sqrt(VALUE);
    printf("Hello, World!\n%.6f\n%.6f\n", squa,sqrt_approx(VALUE));
    
    printPaths(createNodes());
    
    return 0;
}


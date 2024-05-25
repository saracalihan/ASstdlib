/*
 * Copyright (c) 2023, Alihan SARAÇ <saracalihan@gmail.com>
 *
 * This file is under the "MIT" license. Please read "LICENSE" file for more detail.
 */

// statement expression | gcc c lang feature
/* Example usage
    int a = LAMBDA({
        int b = 5;
        int c = 2;
        // some code here

        b*c; // return value
    });
*/
#define LAMBDA(body) \
( \
    body \
)

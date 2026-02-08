
/*
1. Write a C program to swap the content of 2 variables entered through the
command line using function and pointer.
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

int main(int argc, char *argv[]) {

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("Before: a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("After: a=%d, b=%d\n", a, b);
    return 0;
}

/**
Write a C program to check whether the Host machine is in Little Endian or
Big Endian. Enter a number, print the content of each byte location and
Convert the Endianness of the same i.e. Little to Big Endian 
*/


#include <stdio.h>

int main() {
    unsigned int n = 1;
    char *c = (char*)&n;
    if (*c) {
        printf("System is Little Endian.\n");
    } else {
        printf("System is Big Endian.\n");
    }

    unsigned int num = 0x12345678;
    printf("\nOriginal Num: 0x%X\n", num);
    
    char *p = (char*)&num;
    printf("Bytes: 0x%X 0x%X 0x%X 0x%X\n", p[0], p[1], p[2], p[3]);

    unsigned int swapped_num = ((num >> 24) & 0xff) |
                               ((num << 8) & 0xff0000) |
                               ((num >> 8) & 0xff00) |
                               ((num << 24) & 0xff000000);

    printf("Swapped Num: 0x%X\n", swapped_num);
    
    p = (char*)&swapped_num;
    printf("Swapped Bytes: 0x%X 0x%X 0x%X 0x%X\n", p[0], p[1], p[2], p[3]);

    return 0;
}

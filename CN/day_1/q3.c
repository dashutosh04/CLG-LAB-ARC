/*Write a C program to extract each byte from a given number and store them in
separate character variables and print the content of those variable*/

#include <stdio.h>

int main() {
    unsigned int num = 0x1A2B3C4D;
    unsigned char b1, b2, b3, b4;

    b1 = (num >> 24) & 0xFF;
    b2 = (num >> 16) & 0xFF;
    b3 = (num >> 8) & 0xFF;
    b4 = num & 0xFF;

    printf("Original: 0x%X\n", num);
    printf("Bytes: b1=0x%X, b2=0x%X, b3=0x%X, b4=0x%X\n", b1, b2, b3, b4);
    
    return 0;
}

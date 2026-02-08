/*
Write a C Program to enter a number and store the number across the
following structure and print the content of each member of the structure. 
Then aggregate each member of the structure to form the original number and
print the same.
*/

#include <stdio.h>

struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    unsigned int num = 0xABCD1234;
    struct pkt *p = (struct pkt*)&num;
    
    printf("Original Number: 0x%X\n", num);
    printf("--- Stored in Struct ---\n");
    printf("ch1: 0x%X\n", p->ch1);
    printf("ch2[0]: 0x%X\n", p->ch2[0]);
    printf("ch2[1]: 0x%X\n", p->ch2[1]);
    printf("ch3: 0x%X\n", p->ch3);

    unsigned int new_num = 0;
    char *ptr = (char*)&new_num;
    ptr[0] = p->ch1;
    ptr[1] = p->ch2[0];
    ptr[2] = p->ch2[1];
    ptr[3] = p->ch3;

    printf("\nAggregated Number: 0x%X\n", new_num);

    return 0;
}

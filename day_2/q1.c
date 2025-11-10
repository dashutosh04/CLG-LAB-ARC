/*
Aim of the program: Write a program in C to convert the first ‘n’ decimal numbers of a disc
file to binary using recursion. Store the binary value in a separate disc file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int int2bin(int num)
{
    if (num <= 1)
        return num;
    return num % 2 + int2bin(num / 2) * 10;
}

int main(int argc, char **argv)
{
    printf("Amount of num to read: %s\n", argv[1]);

    FILE *inputfile, *outputfile;

    inputfile = fopen(argv[2], "r");
    outputfile = fopen(argv[3], "w");

    int numbers[100];
    int ARR_SIZE = 0;

    while (ARR_SIZE < 100 && fscanf(inputfile, "%d", &numbers[ARR_SIZE]) == 1)
    {
        ARR_SIZE++;
    }

    fclose(inputfile);
    printf("%d ", ARR_SIZE);

    printf("Numbers read from file:\n");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        int new = int2bin(numbers[i]);
        fprintf(outputfile, "Binary of %d is %d\n", numbers[i], new);
    }
    fclose(outputfile);
    printf("\n");
}
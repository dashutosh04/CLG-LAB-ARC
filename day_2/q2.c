/*
Aim of the program: Write a program in C to find GCD of two numbers using recursion. Read
all pair of numbers from a file and store the result in a separate file.
 */

#include <stdio.h>
#include <stdlib.h>

int GCD(int n1, int n2) {
    if (n2 == 0) {
        return n1;
    }
    return GCD(n2, n1 % n2);
}

int main() {
    FILE *in_file, *out_file;
    int n1, n2, gcd_val;

    in_file = fopen("./files/inGCD.dat", "r");

    out_file = fopen("./files/outGCD.dat", "w");

    while (fscanf(in_file, "%d %d", &n1, &n2) == 2) {
        gcd_val = GCD(n1, n2);
        fprintf(out_file, "GCD(%d, %d) = %d\n", n1, n2, gcd_val);
    }

    fclose(in_file);
    fclose(out_file);

    printf("Done. Results are in output.txt.\n");

    return 0;
}

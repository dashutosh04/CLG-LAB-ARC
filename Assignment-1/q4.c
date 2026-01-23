/*
1.4 Write a menu driven program to create a structure to represent complex number and perform the following operation using function :

1. addition of two complex number  (call by value)
2. multiplication of two complex number (call by address)

*/

#include <stdio.h>

struct Complex
{
    float real, imag;
};

struct Complex add(struct Complex c1, struct Complex c2)
{
    struct Complex sum;

    sum.real = c1.real + c2.real;
    sum.imag = c1.imag + c2.imag;
    return sum;
}

struct Complex multiply(struct Complex c1, struct Complex c2)
{

    c1.real = c1.real * c2.real - c1.imag * c2.imag;
    c1.imag = c1.real * c2.imag + c1.imag * c2.real;

}

void display(struct Complex c)
{
    printf("%.2f + %.2fi\n", c.real, c.imag);
}

int main()
{
    int choice;
    do
    {
        struct Complex c1, c2, result;

        printf("Enter complex number 1: ");
        if (scanf("%f %f", &c1.real, &c1.imag) != 2)
        {
            printf("Invalid input. Please enter two numbers.\n");
            continue;
        }

        printf("Enter complex number 2: ");
        if (scanf("%f %f", &c2.real, &c2.imag) != 2)
        {
            printf("Invalid input. Please enter two numbers.\n");
            break;
        }

        printf("\nMENU\n");
        printf("1. addition\n");
        printf("2. multiplication\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 2)
        {
            printf("Invalid choice. Please enter 1 or 2.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            result = add(c1, c2);
            printf("\nSum = ");
            display(result);
            break;
        case 2:
            multiply(c1, c2);
            printf("\nProduct = ");
            display(c1);
            break;
        }
    } while (1);

    return 0;
}

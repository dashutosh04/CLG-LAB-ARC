/*
1.1 Write a program to read two numbers and compare the numbers using function call by address.
*/

#include <stdio.h>

int compare(int *a, int *b)
{
    if (*a > *b)
        return 1;

    else if (*a < *b)
        return -1;

    else
        return 0;
}

int main()
{

    int num1, num2;

    printf("Enter the first number to compare: ");
    scanf("%d", &num1);
    printf("Enter the second number to compare: ");
    scanf("%d", &num2);

    int res = compare(&num1, &num2);

    if (!res)
    {
        printf("Both the numbers are equal.\n");
    }
    else if (res == 1)
    {
        printf("%d is greater than %d.\n", num1, num2);
    }
    else
    {
        printf("%d is smaller than %d.\n", num1, num2);
    }
}

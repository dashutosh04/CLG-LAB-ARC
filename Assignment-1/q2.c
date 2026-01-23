/*
1.2 Write a program to create an array of n elements using dynamic memory allocation.
Calculate sum of all the prime elements of the array using function and de-allocate
the memory of the array after its use.
*/

#include <stdio.h>
#include <stdlib.h>

int prime_checker(int unchecked_int)
{

    // assuming numbers below 2 are not prime..
    if (unchecked_int <= 1)
        return 0;

    for (int i = 2; i * i <= unchecked_int; i++)
    {
        if (unchecked_int % i == 0)
            return 0;
    }
    return 1;
}

int prime_adder(int *arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (prime_checker(arr[i]))
            sum += arr[i];
    }
    return sum;
}

int main()
{
    int n;
    printf("Enter the number of elements for the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    if (!arr)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    printf("Enter the array elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Array elements are: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("Sum of prime elements are: %d\n", prime_adder(arr, n));

    free(arr);
}



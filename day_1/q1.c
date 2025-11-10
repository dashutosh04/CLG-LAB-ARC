/*
1.1 Aim of the program: Write a program to find out the second smallest and second largest element
stored in an array of n integers.
Input: Size of the array is ‘n’ and read ‘n’ number of elements from a disc file.
Output: Second smallest, Second largest
*/

#define ARR_FILE "./files/arr.txt"

#include <stdio.h>
#include <string.h>

int sortArr(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int Swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                Swapped = 1;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }

        if (!Swapped)
            return 0;
    }
}

int main()
{
    printf("Initializing Program. \n");

    FILE *fptr;

    fptr = fopen(ARR_FILE, "r");
    if (fptr == NULL)
    {
        printf("File was not found. Creating file...");
        fptr = fopen(ARR_FILE, "w");
        if (fptr != NULL)
        {
            printf("File was created successfully, restart the program, after filling in the data. \n");
        }
        return 1;
    }

    int numbers[100];
    int ARR_SIZE = 0;

    while (ARR_SIZE < 100 && fscanf(fptr, "%d", &numbers[ARR_SIZE]) == 1)
    {
        ARR_SIZE++;
    }

    fclose(fptr);

    printf("Numbers read from file:\n");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    sortArr(numbers, ARR_SIZE);

    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    printf("Second smallest Element = %d \n", numbers[1]);
    printf("Second largest Element = %d \n", numbers[ARR_SIZE - 2]);
}

/*
Write a program to implement randomized quicksort.
*/ \
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int randomizePivot(int arr[], int low, int high)
{
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return arr[high];
}

int partition(int arr[], int low, int high)
{
    int pivot = randomizePivot(arr, low, high);
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));

    int n;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input! Please enter a positive number.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("Element %d: ", i + 1);
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid input! Exiting...\n");
            free(arr);
            return 1;
        }
    }

    printf("\nOriginal array: ");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Sorted array:   ");
    printArray(arr, n);

    free(arr);
    return 0;
}
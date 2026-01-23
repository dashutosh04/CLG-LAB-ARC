#include <stdio.h>

void selectionSort(int arr[], int size)
{

    for (int i = 0; i < size - 1; i++)
    {
        int smallidx = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[smallidx] > arr[j])
            {
                smallidx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[smallidx];
        arr[smallidx] = temp;
    }
}

int main()
{

    int size;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Original Array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    selectionSort(arr, size);

    printf("\nSorted Array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}
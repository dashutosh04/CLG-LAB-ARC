/*
Implement insertion Sort
*/

#include <stdio.h>
#include <time.h>

void iSort(int arr[], int n, int order)
{
    clock_t t;
    int f;

    t = clock();
    int i, j, key;

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        if (order == 1)
        {
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
        }
        else if (order == 2)
        {
            while (j >= 0 && arr[j] < key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
        }
        arr[j + 1] = key;
    }
    t = clock() - t;

    printf("No. of clicks %ld clicks (%f seconds).\n",
           t, ((float)t) / CLOCKS_PER_SEC);
}

int main()
{
    time_t start, end, fstart, fend;

    start = time(NULL);

    int size;

    printf("Enter the size of the array: \n");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the array contents: \n");

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    int order;

    printf("Enter 1 for Ascending and 2 for Descending: \n");
    scanf("%d", &order);

    if (order != 1 && order != 2)
    {
        perror("Invalid option selected:\n");
        return 0;
    }

    iSort(arr, size, order);

    printf("The array contents after sorting: \n");

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    end = time(NULL);

    printf("\nTime taken to print sum is %.2f seconds",
           difftime(end, start));
}
/**
 * Implement linear search algorithm.
 */

#include <stdio.h>

int linearSearch(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    return -1;
}

int main()
{

    int size, tar;

    printf("Enter the size of the array: \n");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the array contents: \n");

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to be searched : \n");
    scanf("%d", &tar);

    int res = linearSearch(arr, size, tar);

    if (res < 0)
    {
        perror("The given number was not found in the entered array: \n");
    }
    else
    {
        printf("The number was found at index - %d\n", res);
    }
}
/*
WAP to create a one dimensional array of n element and perform the following operations using a
menu based program.
1. Insert a element at specified position.
2. Delete an element from its specified position from the array.
3. Perform linear search to search in the array.
4. Display the array elements.
*/

#include <stdio.h>
#include <stdlib.h>

int insert(int arr[], int n, int pos, int elem)
{
    if (pos < 0 || pos > n)
    {
        printf("Invalid position!\n");
        return 0;
    }

    for (int i = n - 1; i >= pos; i--)
    {
        arr[i + 1] = arr[i];
    }

    arr[pos] = elem;
    return 1;
}

int pop(int arr[], int n, int pos)
{
    if (pos < 0 || pos >= n)
    {
        printf("Invalid position!\n");
        return 0;
    }

    for (int i = pos; i < n - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    return 1;
}

int in(int arr[], int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            return i;
        }
    }
    return -1;
}

void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n, selector, pos, elem, key;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    while (1)
    {
        printf("\n========= Menu =========\n");
        printf("1. Insert an element\n");
        printf("2. Delete an element\n");
        printf("3. Search an element\n");
        printf("4. Display the array\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &selector);

        switch (selector)
        {
        case 1:
            printf("Enter the position and element to insert: ");
            scanf("%d %d", &pos, &elem);
            if (insert(arr, n, pos, elem))
            {
                n++;
                printf("Element inserted...\n");
            }
            break;

        case 2:
            printf("Enter the position of the element to delete: ");
            scanf("%d", &pos);
            if (pop(arr, n, pos))
            {
                {
                    n--;
                    printf("Element Remove...\n");
                }
            }
            break;

        case 3:
            printf("Enter the element to search: ");
            scanf("%d", &key);
            pos = in(arr, n, key);

            if (pos == -1)
            {
                printf("Element not found\n");
            }
            else
            {
                printf("Element found at position %d\n", pos + 1);
            }
            break;

        case 4:
            print(arr, n);
            break;
        case 5:
            printf("Exiting...\n");
            abort();
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

/*Aim of the program: Write a program to read ‘n’ integers from a disc file that must contain
some duplicate values and store them into an array. Perform the following operations on the array.
a) Find out the total number of duplicate elements.
b) Find out the most repeating element in the array.*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_ENTRIES 100

struct FreqInfo
{
    int num;
    int count;
};

int find(struct FreqInfo ft[], int size, int num)
{
    for (int i = 0; i < size; i++)
    {
        if (ft[i].num == num)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    FILE *file;
    int arr[100];
    int n, i;

    file = fopen("./files/arr.txt", "r");

    printf("Duplicate Analysis:\n");
    printf("Nums to read: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        if (fscanf(file, "%d", &arr[i]) != 1)
        {
            printf("Err: Not enough numbers in file.\n");
            n = i;
            break;
        }
    }
    fclose(file);

    printf("Array: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (n == 0)
    {
        printf("Empty array.\n");
        return 0;
    }

    struct FreqInfo ft[MAX_ENTRIES];
    int uc = 0; // unique count

    for (i = 0; i < n; i++)
    {
        int index = find(ft, uc, arr[i]);
        if (index != -1)
        {
            ft[index].count++;
        }
        else
        {
            if (uc < MAX_ENTRIES)
            {
                ft[uc].num = arr[i];
                ft[uc].count = 1;
                uc++;
            }
        }
    }

    int dupCount = 0;
    for (i = 0; i < uc; i++)
    {
        if (ft[i].count > 1)
        {
            dupCount++;
        }
    }
    printf("Duplicates: %d\n", dupCount);

    int max = 0;
    int mostFreq = -1;
    if (uc > 0)
    {
        mostFreq = ft[0].num;
        max = ft[0].count;
    }

    for (i = 1; i < uc; i++)
    {
        if (ft[i].count > max)
        {
            max = ft[i].count;
            mostFreq = ft[i].num;
        }
    }
    printf("Most frequent: %d\n", mostFreq);

    return 0;
}

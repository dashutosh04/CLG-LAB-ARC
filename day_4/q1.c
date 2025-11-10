/*
Write a menu driven program to sort list of array elements using Merge
Sort technique and calculate the execution time only to sort the elements. Count the number of
comparisons.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merger(int arr[], int l, int m, int h, long long int *c)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = h - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        (*c)++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergerSort(int arr[], int l, int h, long long int *c)
{
    if (l < h)
    {
        int m = l + (h - l) / 2;
        mergerSort(arr, l, m, c);
        mergerSort(arr, m + 1, h, c);
        merger(arr, l, m, h, c);
    }
}

void process(const char *fin, const char *fout)
{
    FILE *fpi, *fpo;
    int arr[100000];
    int n = 0, i;
    long long int c = 0;
    long double t;
    clock_t s, e;

    fpi = fopen(fin, "r");
    if (fpi == NULL)
    {
        printf("Input file '%s' not found.\n", fin);
        return;
    }

    while (fscanf(fpi, "%d", &arr[n]) != EOF)
    {
        n++;
    }
    fclose(fpi);

    printf("Before Sorting: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    s = clock();
    mergerSort(arr, 0, n - 1, &c);
    e = clock();

    t = ((double)(s - e) * 1e9) / CLOCKS_PER_SEC;

    fpo = fopen(fout, "w");
    if (fpo == NULL)
    {
        printf("Could not create output file '%s'.\n", fout);
        return;
    }

    printf("After Sorting: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
        fprintf(fpo, "%d ", arr[i]);
    }
    printf("\n");
    fclose(fpo);

    printf("Number of Comparisons: %lld\n", c);
    printf("Execution Time: %.2f nanoseconds\n", t);
}

int main()
{
    int ch;
    while (1)
    {
        printf("\n-------- MAIN MENU --------\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. Exit\n");
        printf("Enter option: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            process("inAsce.dat", "outMergeAsce.dat");
            break;
        case 2:
            process("inDesc.dat", "outMergeDesc.dat");
            break;
        case 3:
            process("inRand.dat", "outMergeRand.dat");
            break;
        case 4:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}

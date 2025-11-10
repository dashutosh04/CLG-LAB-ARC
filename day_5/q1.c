
/*
Write a menu driven program to sort a list of elements in ascending order
using Quick Sort technique. Each choice for the input data has its own disc file. A separate output
file can be used for sorted elements. After sorting display the content of the output file along with
number of comparisons.
Based on the partitioning position for each recursive call, conclude the
input scenario is either best-case partitioning or worst-case partitioning. mnb
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

int wc = 0;
int bc = 0;

int partition(int arr[], int left, int right, int *comparisons)
{
    int pivot = arr[right];
    int i = (left - 1);

    for (int j = left; j <= right - 1; j++)
    {

        if (arr[j] <= pivot)

        {
            (*comparisons)++;
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;
    return (i + 1);
}

int scenario(int p, int left, int right, int *wc_couter, int *bc_counter)
{
    int left_size = p - left;
    int right_size = right - p;
    if (left_size == 0 || right_size == 0)
    {
        (*wc_couter)++;
    }
    else
    {
        (*bc_counter)++;
    }
}

void quickSort(int arr[], int left, int right, int *comparisons)
{

    if (left < right)
    {
        int p = partition(arr, left, right, comparisons);

        scenario(p, left, right, &wc, &bc);
        quickSort(arr, left, p - 1, comparisons);
        quickSort(arr, p + 1, right, comparisons);
    }
}

int process(const char *inputFile, const char *outputFile)
{
    int arr[MAX], n = 0, comparisons = 0;
    long double t;
    clock_t s, e;

    FILE *inF = fopen(inputFile, "r");
    if (inF == NULL)
    {
        printf("Error in File\n");
        return -1;
    }

    while (fscanf(inF, "%d", &arr[n]) != EOF)
    {
        n++;
    }

    fclose(inF);

    s = clock();
    quickSort(arr, 0, n - 1, &comparisons);
    e = clock();

    t = (long double)(e - s) / CLOCKS_PER_SEC;

    FILE *outFile = fopen(outputFile, "w");
    if (outFile == NULL)
    {
        printf("Error opening output file.\n");
        return -1;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(outFile, "%d ", arr[i]);
    }
    fclose(outFile);

    printf("Written to - %s\n", outputFile);
    printf("Number of comparisons: %d\n", comparisons);
    printf("Time taken to sort: %Lf nanoseconds\n", t);
    printf("Number of best case recurssions - %d \n", bc);
    printf("Number of worst case recurssions - %d \n", wc);

    if (bc - wc > 0)
    {
        printf("Conclusion: Best Case\n");
    }
    else
    {
        printf("Conclusion: Worst Case\n");
    }

    return 0;
}

int main()
{
    int ch;
    while (1)
    {
        bc = 0;
        wc = 0;
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
            process("inAsce.dat", "outQuickAsce.dat");
            break;
        case 2:
            process("inDesc.dat", "outQuickDesc.dat");
            break;
        case 3:
            process("inRand.dat", "outQuickRand.dat");
            break;
        case 4:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid option.\n");
        }
    }
    return 0;
}

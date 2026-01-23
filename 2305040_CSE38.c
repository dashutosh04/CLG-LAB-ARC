/*
Name - Ashutosh Das
Roll No - 2305040
Section - CSE38
Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Bubble Sort

/*
In bubble sort alorithm, there are 2 loops,
The first loop iterates through the array
The second loop compares if the next adjecent element
is less than the current element, if true it swaps the element using `temp`.
This loop runs until the array is sorted.
I am using `Swapped` variable to detect if any swapping occurs.
If no swapping occurs then we exit the loop, saving time.

Best Case - O(n) - Here the array is already sorted so the inner loop does not run
Average Case - O(n^2) - Here the array is iterated twice (inner loop runs) so the time complexity is n^2
Worst Case - O(n^2) - Here the array is sorted reverse and most number of iterations are required so the time complexity is n^2

*/

int bubbleSort(int arr[], int n)
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

// Insertion Sort

/*
In Insertion Sort, I am using 2 loops (for loop and while loop),
the outer loop runs for each number of element, and we store the current value in `cur`.
We put the value of j as `j-1` which we will use to replace the values.
if the previous value is smaller than the current value, we put the value of arr[j] in arr[j+1]
then we decrement the value of j. (So the loop will end when j reaches -1)
Then we put current value in arr[j+1].

Best Case - O(n) - Here the array is already sorted so the inner loop does not run
Average Case - O(n^2) - Here the array is iterated twice (inner loop runs) so the time complexity is n^2
Worst Case - O(n^2) - Here the array is sorted reverse and most number of iterations are required so the time complexity is n^2

*/

void insertionSort(int arr[], int n)
{

    int cur, j;
    for (int i = 1; i < n; i++)
    {
        cur = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] < cur)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = cur;
    }
}

// Selection Sort

/*
In Selection Sort, we iterate through the array, finding the smallest element and swapping it with the current element.
The outer loop runs for each element. Then we assume `i` as the smallest index and store it in `s`.
The inner loops runs for the remaining elements and compare them to the smallest element,
and if a smaller element is found it replaces it with the current element, and its index is stored in `s`.
and swapping is done.

Best Case -  O(n^2) - Even if the array is sorted, both the loops run.
Average Case -  O(n^2) - The inner loop runs for half of the remaining elements on average.
Worst Case -  O(n^2) - The array is sorted in reverse order, both the loop runs for each element.
*/

void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int s = i; // Assume the current position i is the smallest
        for (int j = i + 1; j < size; j++)
        {
            if (arr[s] > arr[j]) // Find the smallest element in the unsorted part
            {
                s = j; // Update the index of the smallest element
            }
        }
        // Swap the found smallest element with the first element of the unsorted part
        int temp = arr[i];
        arr[i] = arr[s];
        arr[s] = temp;
    }
}


// Quick Sort

/*
In Quick Sort we use divide-and-conquer algorithm.
First we pick an element, divide the array, and then recursively sort the subarrays.

In partitioning, First we choose a pivot element, then we iterate through the array comparing each element with the pivot element.
Smaller elelements are placed in the left and larger on the right.

Then we apply quick sort recursively on both sides of the array. (left and right)

Best Case -  O(nlogn) - The array is already sorted and it runs the least number of times.
Average Case -  O(nlogn) - In average case, the pivot element divides the array equally (on an average).
Worst Case -  O(n^2) - The pivot is choosen such that it leads to un balancing.

*/

int parter(int arr[], int left, int right)
{
    int pivot = arr[right];
    int i = (left - 1);

    for (int j = left; j <= right - 1; j++)
    {
        if (arr[j] <= pivot)
        {
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

void quickSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int p = parter(arr, left, right);
        quickSort(arr, left, p - 1);
        quickSort(arr, p + 1, right);
    }
}

// Merge Sort

/*

Like quick sort merge sort also uses divide and conquer to sort.
It breaks into two halves, then sort each half, then merge them into one.

The array is divided recursively until it happens only one element.

The smaller arrays are sorted and stored pair wise, by comparing them other subarrays and stores it in temp array.

After the execution the arrays are merged into one, and we have a sorted array.

Best Case -  O(nlogn) - The array is already sorted.
Average Case -  O(nlogn) - The array is randomly stored and only a few iterations required.
Worst Case -  O(nlogn) - The array is sorted in reverse.

*/

void merger(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
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

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merger(arr, left, mid, right);
    }
}


// Just prints the array passed.
void array_print(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


// Main function.
// Asks the user to input array elements and select the sorting algorithm, initally and after each sorting operation.
int main()
{
    int n, choice;

    while (1)
    {
        printf("Enter the size of the array: ");
        scanf("%d", &n);

        int arr[n];
        printf("Enter the elements of the array: ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &arr[i]);
        }

        array_print(arr, n);

        printf("\nChoose a sorting algorithm:\n");
        printf("1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Quick Sort\n5. Merge Sort\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            bubbleSort(arr, n);
            printf("Sorted array: ");
            array_print(arr, n);

            break;
        case 2:

            insertionSort(arr, n);
            printf("Sorted array: ");
            array_print(arr, n);

            break;
        case 3:

            selectionSort(arr, n);
            printf("Sorted array: ");
            array_print(arr, n);

            break;
        case 4:

            quickSort(arr, 0, n - 1);
            printf("Sorted array: ");
            array_print(arr, n);

            break;
        case 5:

            mergeSort(arr, 0, n - 1);
            printf("Sorted array: ");
            array_print(arr, n);

            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

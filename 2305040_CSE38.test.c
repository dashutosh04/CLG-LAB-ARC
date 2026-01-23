#include <stdio.h>

// Function prototype for the selectionSort function to be tested
void selectionSort(int arr[], int size);

// Helper function to compare two arrays
int arraysAreEqual(int arr1[], int arr2[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }
    return 1;
}

int test_selectionSort_sortedArray() {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int size = 5;

    selectionSort(arr, size);

    if (arraysAreEqual(arr, expected, size)) {
        printf("Test Passed: Sorted array remains sorted.\n");
        return 1;
    } else {
        printf("Test Failed: Sorted array was altered.\n");
        return 0;
    }
}

int main() {
    return 0;
}

#include <stdio.h>
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selection_sort(int arr[], int n, int order) {
    int i, j, min_idx, max_idx;

    for (i = 0; i < n - 1; i++) {
    
        min_idx = i;
        max_idx = i;

        
        for (j = i + 1; j < n; j++) {
            if (order == 1) { 
                if (arr[j] < arr[min_idx])
                    min_idx = j;
            } else if (order == -1) { 
                if (arr[j] > arr[max_idx])
                    max_idx = j;
            }
        }

        
        if (order == 1) {
            if (min_idx != i)
                swap(&arr[min_idx], &arr[i]);
        } else if (order == -1) {
            if (max_idx != i)
                swap(&arr[max_idx], &arr[i]);
        }
    }
}


int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

  
    selection_sort(arr, n, 1);

    printf("\nArray sorted in ascending order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

 
    selection_sort(arr, n, -1);

    printf("\nArray sorted in descending order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
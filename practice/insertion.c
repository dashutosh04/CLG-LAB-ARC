#include <stdio.h>

void insertionSort(int arr[],int n){

    int cur,j;

    for(int i = 1;i<n;i++){

        cur = arr[i];
        j = i - 1;

        while(j>=0 && arr[j] < cur){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = cur;
    }

}

int main()
{

    int size = 0;
    printf("Enter the size of array: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter the elements of array: ");
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    printf("Original Array: ");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    insertionSort(arr,size);

    printf("Sorted Array: ");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);

}}
/*
Aim of the program: Write a program to find the maximum profit nearest to but not exceeding
the given knapsack capacity using the Fractional Knapsack algorithm.
Notes# Declare a structure ITEM having data members item_id, item_profit, item_weight and
profit_weight_ratio. Apply heap sort technique to sort the items in non-increasing order, according
to their profit/weight.

*/

#include <stdio.h>
#include <stdlib.h>

struct ITEM
{
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

void swap(struct ITEM *a, struct ITEM *b)
{
    struct ITEM temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct ITEM arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio < arr[largest].profit_weight_ratio)
        largest = left;
    if (right < n && arr[right].profit_weight_ratio < arr[largest].profit_weight_ratio)
        largest = right;

    if (largest != i)
    {
        struct ITEM temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(struct ITEM arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        struct ITEM temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main()
{
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM *items = (struct ITEM *)malloc(n * sizeof(struct ITEM));
    for (int i = 0; i < n; i++)
    {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
       }

    float capacity;
    printf("Enter the capacity of knapsack:");
    scanf("%f", &capacity);

    heapSort(items, n);

    float max_profit = 0.0;
    float *amount_taken = (float *)calloc(n, sizeof(float));
    float remaining = capacity;

    for (int i = 0; i < n; i++)
    {
        if (items[i].item_weight <= remaining)
        {
            amount_taken[i] = 1.0;
            max_profit += items[i].item_profit;
            remaining -= items[i].item_weight;
        }
        else if (remaining > 0)
        {
            amount_taken[i] = remaining / items[i].item_weight;
            max_profit += items[i].item_profit * amount_taken[i];
            remaining = 0;
        }
        else
        {
            amount_taken[i] = 0.0;
        }
    }

    printf("Item_No\tProfit\t\tWeight\t\tAmount to be taken\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%.6f\t%.6f\t%.6f\n", i + 1, items[i].item_profit, items[i].item_weight, amount_taken[i]);
    }
    printf("Maximum profit: %.6f\n", max_profit);

    free(items);
    free(amount_taken);
    return 0;
}

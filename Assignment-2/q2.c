/*
WAP to perform the following operations on the given sqare matrix using functions.
1. Find the number of nonzeros in the given matrix.
2. Display the upper triangular matrix.
3. Display all the elements except the diagonal.
*/

#include <stdio.h>

int non_zero(int mat[][100], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] != 0)
            {
                count++;
            }
        }
    }
    return count;
}

void print_up_triangle(int mat[][100], int n)
{
    printf("Upper triangular matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i > j)
            {
                printf("%d ", mat[i][j]);
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void print_non_diagnol(int mat[][100], int n)
{
    printf("Non-diagonal elements:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                printf("%d ", mat[i][j]);
            }
        }
    }
    printf("\n");
}

int main()
{
    int n = 0;
    printf("Enter the size of the square matrix: ");
    scanf("%d", &n);

    int mat[100][100];

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }

    printf("Number of non-zeros: %d\n", non_zero(mat, n));
    print_up_triangle(mat, n);
    print_non_diagnol(mat, n);

    return 0;
}

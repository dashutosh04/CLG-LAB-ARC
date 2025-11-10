#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 100

typedef struct
{
    int rows, cols;
} Matrix;

void print_m_table(int m[][MAX], int n)
{
    printf("M Table:\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j || i > j)
                printf("0 ");
            else
                printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void print_s_table(int s[][MAX], int n)
{
    printf("S Table:\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i >= j)
                printf("0 ");
            else
                printf("%d ", s[i][j]);
        }
        printf("\n");
    }
}

void print_parenthesization(int s[][MAX], int i, int j, char *result, int *index)
{
    if (i == j)
    {
        result[(*index)++] = 'A';
        sprintf(result + *index, "%d", i);
        *index += (i >= 10 ? 2 : 1);
        return;
    }
    result[(*index)++] = '(';
    print_parenthesization(s, i, s[i][j], result, index);
    print_parenthesization(s, s[i][j] + 1, j, result, index);
    result[(*index)++] = ')';
    result[*index] = '\0';
}

void matrix_chain_multiplication(Matrix matrices[], int n)
{
    int m[MAX][MAX] = {0};
    int s[MAX][MAX] = {0};
    int p[MAX + 1];

    for (int i = 0; i < n; i++)
    {
        p[i] = matrices[i].rows;
        if (i > 0 && matrices[i - 1].cols != matrices[i].rows)
        {
            printf("Error:");
            return;
        }
    }
    p[n] = matrices[n - 1].cols;

    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i <= n - len + 1; i++)
        {
            int j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    print_m_table(m, n);
    print_s_table(s, n);

    char result[1000];
    int index = 0;
    result[0] = '\0';
    print_parenthesization(s, 1, n, result, &index);

    printf("Optimal parenthesization: %s\n", result);
    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n]);
}

int main()
{
    int n;
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    Matrix *matrices = (Matrix *)malloc(n * sizeof(Matrix));

    for (int i = 0; i < n; i++)
    {
        printf("Enter row and col size of A%d: ", i + 1);
        scanf("%d %d", &matrices[i].rows, &matrices[i].cols);
    }

    matrix_chain_multiplication(matrices, n);

    free(matrices);
    return 0;
}
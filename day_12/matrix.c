#include <stdio.h>
#include <limits.h>

void print_parenth(int s[][101], int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }
    printf("(");
    print_parenth(s, i, s[i][j]);
    print_parenth(s, s[i][j] + 1, j);
    printf(")");
}

int main(void)
{
    int n;
    printf("Enter number of matrices: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of matrices.\n");
        return 1;
    }

    int rows, cols;
    int p[101];
    int prev_cols = -1;
    for (int i = 0; i < n; ++i)
    {
        printf("Enter rows and cols of A%d: ", i + 1);
        if (scanf("%d %d", &rows, &cols) != 2)
        {
            printf("Invalid input.\n");
            return 1;
        }
        if (i == 0)
            p[0] = rows;
        else if (prev_cols != rows)
        {
            printf("Error: Incompatible dimensions between A%d and A%d\n", i, i + 1);
            return 1;
        }
        prev_cols = cols;
        p[i + 1] = cols;
    }

    static int m[101][101];
    static int s[101][101];

    for (int i = 1; i <= n; ++i)
        m[i][i] = 0;

    for (int len = 2; len <= n; ++len)
    {
        for (int i = 1; i <= n - len + 1; ++i)
        {
            int j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; ++k)
            {
                long cost = (long)m[i][k] + m[k + 1][j] + (long)p[i - 1] * p[k] * p[j];
                if (cost < m[i][j])
                {
                    m[i][j] = (int)cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Optimal parenthesization: ");
    print_parenth(s, 1, n);
    printf("\nMinimum scalar multiplications: %d\n", m[1][n]);

    return 0;
}

// Implementation of LCS for 2 strings

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int lcs_(char *s1, char *s2)
{
    int m = strlen(s1), n = strlen(s2);

    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    int len = dp[m][n];
    printf("Length of LCS is: %d\n", len);

    char lcs[len + 1];
    lcs[len] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            lcs[len - 1] = s1[i - 1];
            i--;
            j--;
            len--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    printf("LCS is  %s\n", lcs);
    return 0;
}

int main()
{
    char s1[100], s2[100];
    printf("First string: ");
    scanf("%s", s1);
    printf("Second string: ");
    scanf("%s", s2);

    lcs_(s1, s2);

    return 0;
}

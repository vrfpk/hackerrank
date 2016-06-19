#include <stdlib.h>
#include <stdio.h>

#define LCS_MAX 100

int lcs_rec(char X[], char Y[], int m, int n)
{
	int a, b;
	if (m == 0 || n == 0) {
		return 0;
	}
	if (X[m - 1] == Y[n - 1]) {
		return 1 + lcs_rec(X, Y, m - 1, n - 1);
	}
	a = lcs_rec(X, Y, m - 1, n);
	b = lcs_rec(X, Y, m, n - 1);
	return (a > b ? a : b);
}

int lcs_tab(char X[], char Y[], int m, int n) {
    int i, j;
    int dp[LCS_MAX][LCS_MAX];
    
    for (i = 0; i <= m; ++i)
        dp[i][0] = 0;
    for (i = 0; i <= n; ++i)
        dp[0][1] = 0;
    
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            if (X[i-1] == Y[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = (dp[i-1][j] > dp[i][j-1] ? dp[i-1][j] : dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}

int test_lcs_rec()
{
	char X[] = "AGGTAB";
	char Y[] = "GXTXAYB";

	int m = 6;
	int n = 7;

	printf("Length of LCS is %d\n", lcs_rec(X, Y, m, n));
    
    return 0;
}

int test_lcs_tab()
{
	char X[] = "AGGTAB";
	char Y[] = "GXTXAYB";

	int m = 6;
	int n = 7;

	printf("Length of LCS is %d\n", lcs_tab(X, Y, m, n));
    
    return 0;
}

int main()
{
	test_lcs_tab();

	return 0;
}

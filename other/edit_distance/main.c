#include <stdlib.h>
#include <stdio.h>

#define EDIT_MAX 100

int edit_distance_rec(char X[], char Y[], int m, int n) {
    int a, b, c, min;
    if (m == 0) // if X is empty, just insert all Ys
        return n;
    if (n == 0) // if Y is empty, insert all Xs
        return m;
    if (X[m-1] == Y[n-1]) {
        return edit_distance_rec(X, Y, m-1, n-1);
    }
    a = edit_distance_rec(X, Y, m, n-1); // insert from Y to X (so X is 1 shorter)
    b = edit_distance_rec(X, Y, m-1, n); // remove from Y to obtain X (so Y is 1 shorter)
    c = edit_distance_rec(X, Y, m-1, n-1); // replace char X with character from Y (so X and Y is 1 shorter)
    // compute minimum of 3 values above
    min = a;
    if (min > b) min = b;
    if (min > c) min = c;
    return 1 + min;
}

int edit_distance_tab(char X[], char Y[], int m, int n) {
    int i, j, min;
    int dp[EDIT_MAX][EDIT_MAX];
    
    for (i = 0; i <= m; ++i)
        dp[0][i] = i;
    for (i = 0; i <= n; ++i)
        dp[i][0] = i;
    
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                min = dp[i][j-1];
                if (min > dp[i-1][j]) min = dp[i-1][j];
                if (min > dp[i-1][j-1]) min = dp[i-1][j-1];
                dp[i][j] = 1 + min;
            }
        }
    }
    
    return dp[m][n];
}

int test_edit_distance_rec() {
    char str1[] = "sunday";
    char str2[] = "saturday";
    
    printf("edit distance: %d\n", edit_distance_rec(str1, str2, 6, 8));
    return 0;
}

int test_edit_distance_tab() {
    char str1[] = "sunday";
    char str2[] = "saturday";
    
    printf("edit distance: %d\n", edit_distance_tab(str1, str2, 6, 8));
    return 0;
}

int main()
{
    test_edit_distance_tab();
	return 0;
}

#include "algorithms.h"
#include "lcs.h"

int lcs_rec(char X[], int m, char Y[], int n)
{
	int a, b;
	if (m == 0 || n == 0)
		return 0;
	if (X[m - 1] == Y[n - 1])
		return 1 + lcs_rec(X, m - 1, Y, n - 1);
	a = lcs_rec(X, m, Y, n - 1);
	b = lcs_rec(X, m - 1, Y, n);
	return (a > b ? a : b);
}

int lcs_mem(char x[], int m, char y[], int n)
{
	int **dp = alloc2d(m, n);

	return 0;
}
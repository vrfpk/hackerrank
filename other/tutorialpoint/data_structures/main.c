#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define A_MAX 100000

int main()
{
	int n, k;
	int i;
	int A[A_MAX] = { 0 };
	freopen("input.txt", "r", stdin);

	scanf("%d %d", &n, &k);
	for (i = 0; i < n; ++i) scanf("%d", &A[i]);
	printf("%d %d\n", n, k);
	for (i = 0; i < n; ++i) printf("%d\n", A[i]);

	return 0;
}

#include <stdlib.h>
#include <stdio.h>

//#include "partition.h"

#define FALSE 0
#define TRUE 1

int ** alloc2d(int n, int m)
{
	int i;
	int **p = (int**) malloc(n * sizeof(int*));
	int *q = (int*) malloc(n * m * sizeof(int));
	for (i = 0; i < n; ++i) p[i] = &q[i*m];
	return p;
}

void delete2d(int **p)
{
	free(p[0]);
	free(p);
}

int find_max_partition(int arr[], int n)
{
	int sum = 0;
	int i, j, s, ret = 0;
	int **dp;
	int tmp1, tmp2, element, check;
	for (i = 0; i < n; ++i)
		sum += arr[i];

	if (sum % 2 != 0)
		sum -= 1;

	dp = alloc2d(sum + 1, n + 1);
	for (i = 0; i < n + 1; ++i)
		dp[0][i] = TRUE;

	for (i = 1; i < sum + 1; ++i)
		dp[i][0] = FALSE;

	for (s = 1; s <= sum; s++) {
		for (i = 1; i <= n; i++) {
			dp[s][i] = dp[s][i - 1];
			if (s >= arr[i - 1])
				dp[s][i] = dp[s][i] || dp[s - arr[i - 1]][i - 1];
		}
	}

	//for (s = sum / 2; s >= 1; s = s - 1) {
	//	if (dp[2 * s][n] == TRUE && dp[s][n] == TRUE) {
	//		ret = s;
	//		break;
	//	}
	//}

	//printf("\n");

	//for (s = sum; s >= 1; --s) {
	//	if (dp[s][n] == FALSE) continue;
	//	printf("%02d: ", s);
	//	tmp1 = s;
	//	while (tmp1 != 0) {
	//		for (i = n; i >= 1; --i) if (dp[tmp1][i] == TRUE && dp[tmp1][i - 1] == FALSE) {
	//			printf("[%02d %d %02d] ", tmp1, i - 1, arr[i - 1]);
	//			tmp1 -= arr[i - 1];
	//			break;
	//		}
	//	}
	//	printf("\n");
	//}
	//printf("\n");
	for (s = sum / 2; s >= 1; --s) {
		if (dp[s][n] == FALSE) continue;
		if (dp[2 * s][n] == FALSE) continue;
		tmp1 = s;
		while (tmp1 != 0) {
			for (i = n; i >= 1; --i) if (dp[tmp1][i] == TRUE && dp[tmp1][i - 1] == FALSE) {
				element = arr[i - 1];
				tmp2 = 2 * s;
				check = 0;
				while (tmp2 != 0) {
					for (j = n; j >= 1; --j) if (dp[tmp2][j] == TRUE && dp[tmp2][j - 1] == FALSE) {
						if (arr[j - 1] == arr[i - 1]) {
							check = 1; tmp2 = 0; break;
						}
						tmp2 -= arr[j - 1];
					}
				}
				if (check == 0) { tmp1 = 0; break; }
				tmp1 -= arr[i - 1];
				break;
			}
		}
		if (check == 1) {
			ret = s; break;
		}
	}

	delete2d(dp);

	return ret;
}

void test_find_max_partition()
{
	 int n = 4;
	 int p = 0;
	 //int i;
	 int arr[] = { 1, 3, 5, 10 };

	 if (0 == (p = find_max_partition(arr, n)))
		printf("arr cannot be equally devided\n");
	else
		printf("best partition: %d\n", p);
}

int main()
{
	test_find_max_partition();

	return 0;
}

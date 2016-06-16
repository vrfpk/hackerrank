#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include "algorithms.h"

#define FALSE 0u
#define TRUE 1u

int is_subset_sum_rec(int arr[], int n, int sum)
{
	if (sum == 0) {
		return 1;
	}
	if (n == 0 && sum != 0) {
		return 0;
	}
	return
		is_subset_sum_rec(arr, n - 1, sum) ||
		is_subset_sum_rec(arr, n - 1, sum - arr[n - 1]);
}

int find_partition_rec(int arr[], int n)
{
	int sum = 0;
	int i;
	for (i = 0; i < n; ++i) {
		sum += arr[i];
	}
	if (sum % 2 != 0) {
		return 0;
	}
	return is_subset_sum_rec(arr, n, sum / 2);
}

int find_partition(int arr[], int n)
{
	int sum = 0;
	int i, j, s;
	int **dp;

	for (i = 0; i < n; ++i)
		sum += arr[i];

	if (sum % 2 != 0)
		return 0;

	dp = alloc2d(sum / 2 + 1, n + 1);
	for (i = 0; i < n + 1; ++i)
		dp[0][i] = 1;

	for (i = 1; i < sum / 2 + 1; ++i)
		dp[i][0] = 0;

	/*
	*  part[s][i] = true if a subset of {arr[0], arr[1], ..arr[i-1]} has sum
	*  equal to s, otherwise false
	*/
	for (s = 1; s <= sum / 2; s++)
		for (i = 1; i <= n; i++) {
			dp[s][i] = dp[s][i - 1];
			if (s >= arr[i - 1])
				dp[s][i] = dp[s][i] || dp[s - arr[i - 1]][i - 1];
		}

	/*
	for (i = 0; i < sum / 2 + 1; ++i) {
	for (j = 0; j < n + 1; ++j)
	printf("%s ", (dp[i][j] == 0) ? "false" : "true ");
	printf("\n");
	}
	*/

	return dp[sum / 2][n];
}

int compare_int(const void *a, const void *b)
{
	return (*(int*) a - *(int*) b);
}

int find_max_partition_rec(int arr[], int n)
{
	int sum = 0;
	int i;
	for (i = 0; i < n; ++i)
		sum += arr[i];

	if (sum % 2 != 0)
		sum -= 1;

	qsort(arr, n, sizeof(int), compare_int);
	for (i = sum; i >= arr[1]; --i)
		if (0 != is_subset_sum_rec(arr, n, i))
			return i;

	return 0;
}

int find_max_partition(int arr[], int n)
{
	int sum = 0;
	int i, j, s;
	int **dp;
	for (i = 0; i < n; ++i)
		sum += arr[i];

	if (sum % 2 != 0)
		sum -= 1;

	dp = alloc2d(sum + 1, n + 1);
	for (i = 0; i < n + 1; ++i)
		dp[0][i] = TRUE;

	for (i = 1; i < sum + 1; ++i)
		dp[i][0] = FALSE;

	for (s = 1; s <= sum; s++)
		for (i = 1; i <= n; i++) {
			dp[s][i] = dp[s][i - 1];
			if (s >= arr[i - 1])
				dp[s][i] = dp[s][i] || dp[s - arr[i - 1]][i - 1];
		}

	/*
	for (s = 0; s < sum + 1; ++s) {
	for (i = 0; i < n + 1; ++i)
	printf("s: %2d %s ", s, (dp[s][i] == FALSE) ? "false" : "true ");
	printf("\n");
	}
	*/

	for (s = sum; s >= 2; s = s - 2)
		if (dp[s][n] == TRUE && dp[s / 2][n] == TRUE)
			return s / 2;

	return 0;
}

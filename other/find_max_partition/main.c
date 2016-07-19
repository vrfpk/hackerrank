#include <malloc.h>
#include <stdio.h>

#define FALSE 0
#define TRUE 1

int** alloc2d(int n, int m) {
	int i;
	int **p = (int**) malloc(n * sizeof(int*));
	int *q = (int*) malloc(n * m * sizeof(int));
	for (i = 0; i < n; ++i) p[i] = &q[i*m];
	return p;
}

void free2d(int **p) {
	free(p[0]);
	free(p);
}

int can_equally_split(int arr[], int n) {
	int sum = 0;
	int i, s, ret = 0;
	int **dp;

	for (i = 0; i < n; ++i)
		sum += arr[i];

	if (sum % 2 != 0)
		return FALSE;

	/* initialize dp array */
	dp = alloc2d(sum / 2 + 1, n + 1);
	for (i = 0; i < n + 1; ++i)
		dp[0][i] = TRUE;

	for (i = 1; i < sum / 2 + 1; ++i)
		dp[i][0] = FALSE;

	/* build dp array
	 * dp[s][i] is true if set Ai: { arr[0], ..., arr[i-1] }
	 * have subset with sum = s. There are two cases:
	 * a) arr[i-1] is part of that subset, so exclude it
	 *    from from Ai and take into account sum = s - arr[i-1]
	 * b) arr[i-1] is not part of that subset, so exclude it but still sum = s; */
	for (s = 1; s <= sum / 2; s++) {
		for (i = 1; i <= n; i++) {
			dp[s][i] = dp[s][i - 1];
			if (s >= arr[i - 1])
				dp[s][i] = dp[s][i] || dp[s - arr[i - 1]][i - 1];
		}
	}
	ret = dp[sum / 2][n];
	free2d(dp);

	return ret;
}

int find_max_partition(int arr[], int n) {
	int sum = 0;
	int i, s, ret = 0;
	int **dp;
	int *a;
	int cnt, p;

	for (i = 0; i < n; ++i)
		sum += arr[i];

	if (sum % 2 != 0)
		sum -= 1;

	/* initialize dp array */
	dp = alloc2d(sum + 1, n + 1);
	for (i = 0; i < n + 1; ++i)
		dp[0][i] = TRUE;

	for (i = 1; i < sum + 1; ++i)
		dp[i][0] = FALSE;

	/* build dp array
	 * dp[s][i] is true if set Ai: { arr[0], ..., arr[i-1] }
	 * have subset with sum = s. There are two cases:
	 * a) arr[i-1] is part of that subset, so exclude it
	 *    from from Ai and take into account sum = s - arr[i-1]
	 * b) arr[i-1] is not part of that subset, so exclude it but still sum = s; */
	for (s = 1; s <= sum; s++) {
		for (i = 1; i <= n; i++) {
			dp[s][i] = dp[s][i - 1];
			if (s >= arr[i - 1])
				dp[s][i] = dp[s][i] || dp[s - arr[i - 1]][i - 1];
		}
	}

	a = (int*) malloc(n * sizeof(int));

	/* If set Arr: { arr[0], ..., arr[n-1] } has two
	 * disjoint subsets with the same sum, Arr has to have
	 * subset A1 with sum = x and A2 with sum = 2*x, and
	 * moreover A1 has to be subset of A2
	 * be careful, checking if dp[s][n] and dp[s/2][n] is TRUE is not enough (A1 and A2 could be disjoint)
	 * moreover, from dp one cannot conclude that A1 \subset A2, bcos there can be two subsets A1a and A1v
	 * with sum x, and unluckily dp algorithm could take wrong one into account, so
	 * A2 has to be checked if can be splited into two equal parts
	 */
	for (s = sum; s >= 2; s -= 2) {
		if (dp[s][n] == FALSE && dp[s / 2][n] == FALSE) continue;
		cnt = 0;
		p = s;
		while (p != 0)
			for (i = n; i >= 1; --i)  if (dp[p][i] == TRUE && dp[p][i - 1] == FALSE) {
				a[cnt++] = arr[i - 1];
				p -= arr[i - 1];
				break;
			}
		if (can_equally_split(a, cnt) == TRUE) {
			ret = s / 2;
			break;
		}
	}

	free(a);
	free2d(dp);

	return ret;
}

void test_find_max_partition() {
	int n = 5;
	int p = 0;
	int arr[] = { 2, 4, 6, 8, 10 };

	if (0 == (p = find_max_partition(arr, n)))
		printf("arr cannot be equally devided\n");
	else
		printf("best partition: %d\n", p);
}

int main() {
	test_find_max_partition();

	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define FALSE 0
#define TRUE 1

using namespace std;

static int** alloc2d(int n, int m)
{
	int i;
	int **p = (int**) malloc(n * sizeof(int*));
	int *q = (int*) malloc(n * m * sizeof(int));
	for (i = 0; i < n; ++i) p[i] = &q[i*m];
	return p;
}

static void free2d(int **p)
{
	free(p[0]);
	free(p);
}

static int compare(const void* p1, const void *p2)
{
	if (*(int*) p1 <  *(int*) p2) return -1;
	if (*(int*) p1 == *(int*) p2) return 0;
	return 1;
}

/* Return 1 if Y is a subset of X */
static int is_subset(int X[], int Y[], int n, int m)
{
	int i = 0, j = 0;
	if (n < m) return 0;
	qsort(X, n, sizeof(int), compare);
	qsort(Y, m, sizeof(int), compare);
	while (i < n && j < m) {
		if (X[i] < Y[j]) {
			i++;
		} else if (X[i] == Y[j]) {
			++i; ++j;
		} else if (X[i] > Y[j]) {
			return 0;
		}
	}
	if (j < m) return 0;
	else return 1;
}

static int find_max_partition(int arr[], int n)
{
	int sum = 0;
	int i, j, s, ret = 0;
	int **dp;
	int p, tmp2, element, check;
	int *a1, *a2;
	int cnt1, cnt2;

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

	//for (s = sum; s >= 1; --s) {
	//	if (dp[s][n] == FALSE) continue;
	//	printf("%02d: ", s);
	//	p = s;
	//	while (p != 0) for (i = n; i >= 1; --i) if (dp[p][i] == TRUE && dp[p][i - 1] == FALSE) {
	//			printf("[%d %02d]", i - 1, arr[i - 1]);
	//			p -= arr[i - 1];
	//			break;
	//		}
	//	printf("\n");
	//}
	//printf("\n");

	a1 = (int*) malloc(n * sizeof(int));
	a2 = (int*) malloc(n * sizeof(int));

	/* If set Arr: { arr[0], ..., arr[n-1] } has two
	 * disjoint subsets with the same sum, Arr has to have
	 * subset A1 with sum = x and A2 with sum = 2*x, and
	 * moreover A1 has to be subset of A2 */
	for (s = sum / 2; s >= 1; --s) {
		if (dp[s][n] == FALSE) continue;
		if (dp[2 * s][n] == FALSE) continue;
		cnt1 = cnt2 = 0;
		p = s;
		while (p != 0)
			for (i = n; i >= 1; --i) if (dp[p][i] == TRUE && dp[p][i - 1] == FALSE) {
				a1[cnt1++] = arr[i - 1];
				p -= arr[i - 1];
				break;
			}
		p = 2 * s;
		while (p != 0)
			for (i = n; i >= 1; --i) if (dp[p][i] == TRUE && dp[p][i - 1] == FALSE) {
				a2[cnt2++] = arr[i - 1];
				p -= arr[i - 1];
				break;
			}
		if (1 == is_subset(a2, a1, cnt2, cnt1)) {
			ret = s;
			break;
		}
	}

	free(a2);
	free(a1);
	free2d(dp);

	return ret;
}

void test_max_partition()
{
    int t, T;
    freopen("max_partition.txt", "r", stdin);
    cin >> T;
    int arr[50];
    for (t = 1; t <= T; ++t) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> arr[i];
        cout << t << "# " << find_max_partition(arr, n) << "\n";
    }
    
}

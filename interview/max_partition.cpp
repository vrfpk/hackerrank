#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define FALSE 0
#define TRUE 1
#define SIZE 1001

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

static int is_subset_sorted(int X[], int Y[], int n, int m)
{
    int i = 0, j = 0;
    if (n < m) return FALSE;
    while (i < n && j < m)
		if (X[i] < Y[j]) {
			i++;
		} else if (X[i] == Y[j]) {
			++i; ++j;
		} else if (X[i] > Y[j]) {
			break;
		}
	if (j < m) return 0;
	else return 1;
}

/* Return 1 if Y is a subset of X */
static int is_subset(int X[], int Y[], int n, int m)
{
	if (n < m) return 0;
	qsort(X, n, sizeof(int), compare);
	qsort(Y, m, sizeof(int), compare);
    return is_subset_sorted(X, Y, n, m);
}

#define PARENT(i) (((i) - 1) >> 1)
#define LEFT(i) (((i) << 1) + 1)
#define RIGHT(i) (((i) << 1) + 2)
#define SWAP(u, v) do { if (u != v) { u=u^v; v=u^v; u=u^v; } } while(0)

void add_to_heap(int *heap, int size, int x) {
    heap[size] = x;
    while (size != 0 && heap[PARENT(size)] < heap[size]) {
        SWAP(heap[PARENT(size)], heap[size]);
        size = PARENT(size);
    }
}

void remove_heap_root(int *heap, int size) {
    int c = 0;
    SWAP(heap[c], heap[size-1]);
    while (1) {
        if (LEFT(c) >= size-1) {
            break;
        } else if (RIGHT(c) >= size-1) {
            if (heap[LEFT(c)] > heap[c]) SWAP(heap[LEFT(c)], heap[c]);
            break;
        } else if (heap[LEFT(c)] > heap[RIGHT(c)] && heap[LEFT(c)] > heap[c]) {
            SWAP(heap[LEFT(c)], heap[c]);
            c = LEFT(c);
        } else if (heap[RIGHT(c)] >= heap[LEFT(c)] && heap[RIGHT(c)] > heap[c]) {
            SWAP(heap[RIGHT(c)], heap[c]);
            c = RIGHT(c);
        } else {
            break;
        }
    }
}

#define EXTRACT(H,C)                                        \
do {                                                        \
    C = 0;                                                  \
    while (p != 0)                                          \
	for (i = n; i >= 1; --i)                                \
        if (dp[p][i] == TRUE && dp[p][i - 1] == FALSE) {    \
            add_to_heap(H, C++, arr[i-1]);                  \
            p -= arr[i - 1];                                \
            break;                                          \
        }                                                   \
    for (i = C; i > 0; --i) remove_heap_root(H, i);         \
} while (0)                                                 \

static int find_max_partition(int arr[], int n)
{
	int sum = 0;
	int i, j, p, ret = 0, s;
	int **dp;
    int *h1, *h2;
    int c1, c2;

	for (i = 0; i < n; ++i) sum += arr[i];

	if (sum % 2 != 0) sum -= 1;

	/* initialize dp array */
	dp = alloc2d(sum + 1, n + 1);
    if (dp == NULL) return 0;
	for (i = 0; i < n + 1; ++i) dp[0][i] = TRUE;
	for (i = 1; i < sum + 1; ++i) dp[i][0] = FALSE;

	/* build dp array
	 * dp[s][i] is true if set Ai: { arr[0], ..., arr[i-1] }
	 * have subset with sum = s. There are two cases:
	 * a) arr[i-1] is part of that subset, so exclude it
	 *    from from Ai and take into account sum = s - arr[i-1]
	 * b) arr[i-1] is not part of that subset, so exclude it but still sum = s; */
	for (s = 1; s <= sum; s++) 
        for (i = 1; i <= n; i++) {
			dp[s][i] = dp[s][i - 1];
			if (s >= arr[i - 1]) dp[s][i] = dp[s][i] || dp[s - arr[i - 1]][i - 1];
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

	h1 = (int*) malloc(n * sizeof(int));
	h2 = (int*) malloc(n * sizeof(int));

    /* If set Arr: { arr[0], ..., arr[n-1] } has two
	 * disjoint subsets with the same sum, Arr has to have
	 * subset A1 with sum = x and A2 with sum = 2*x, and
	 * moreover A1 has to be subset of A2 */
	for (s = sum / 2; s >= 1; --s) {
		if (dp[s][n] == FALSE) continue;
		if (dp[2 * s][n] == FALSE) continue;
		p = s;
//        EXTRACT(h1, c1);
        c1 = 0;
		while (p != 0)
			for (i = n; i >= 1; --i) if (dp[p][i] == TRUE && dp[p][i - 1] == FALSE) {
                //add_to_heap(h1, c1++, arr[i-1]);
                h1[c1++] = arr[i-1];
				p -= arr[i - 1];
				break;
			}
        //for (i = c1; i > 0; --i) remove_heap_root(h1, i);
		p = 2 * s;
//        EXTRACT(h2, c2);
        c2 = 0;
		while (p != 0)
			for (i = n; i >= 1; --i) if (dp[p][i] == TRUE && dp[p][i - 1] == FALSE) {
                //add_to_heap(h2, c2++, arr[i-1]);
                h2[c2++] = arr[i-1];
				p -= arr[i - 1];
				break;
			}
        //for (i = c2; i > 0; --i) remove_heap_root(h2, i);
        // i = j = 0;
        // while (i < c2 && j < c1) {
            // if (h2[i] < h1[j]) i++;
            // else if (h2[i] == h1[j]) ++i, ++j;
            // else if (h2[i] > h1[j]) break;
        // }
        // if (j == c1) {
            // ret = s;
            // break;
        // }
        //if (1 == is_subset_sorted(h2, h1, c2, c1)) {
        if (1 == is_subset(h2, h1, c2, c1)) {
            ret = s;
            #ifdef DEBUG
            printf("s : %03d --> ", s);
            for (i = 0; i < c1; ++i) printf("%02d ", h1[i]);
            printf("\n");
            printf("2s: %03d --> ", 2*s);
            for (i = 0; i < c2; ++i) printf("%02d ", h2[i]);
            printf("\n");
            #endif
            break;
        }
	}

	free(h2);
	free(h1);
	free2d(dp);

	return ret;
}

void test_max_partition()
{
    int t, T;
    freopen("max_partition.txt", "r", stdin);
    cin >> T;
    int arr[SIZE];
    for (t = 1; t <= T; ++t) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> arr[i];
        cout << t << "# " << find_max_partition(arr, n) << "\n";
    }
}
/* old file
4
5
2 3 4 1 6
5
4 18 22 10 4
4
1 3 5 10
6
1 1 1 1 1 1
*/

void create_test_max_partition() {
    int T = 10;
    freopen("max_partition.txt", "w", stdout);
    cout << T << "\n";
    for (int t = 1; t <= T; ++t) {
        int n = 1000; //rand() % 50 + 1;
        cout << n << "\n";
        for (int i = 0; i < n; ++i) cout << rand() % 100 + 1 << " ";
        cout << "\n";
    }
}

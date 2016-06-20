#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <cstdlib>
#include <random>
using namespace std;

void generate_input()
{
	freopen("input.txt", "w", stdout);

	std::default_random_engine generator(1);
	int n = 75000;
	int q = 75000;

	std::uniform_int_distribution<int> distribution_a(-1000000000, 1000000000);
	std::uniform_int_distribution<int> distribution_q(0, n - 1);

	int k = distribution_q(generator);
	cout << n << " " << q << " " << k << "\n";

	for (int i = 0; i < n; ++i) {
		cout << distribution_a(generator) << " ";
	}
	cout << "\n";
	for (int i = 0; i < q; ++i) {
		int a, b;
		a = distribution_q(generator); b = distribution_q(generator);
		if (a == b) b++;
		else if (a > b) { a = a ^ b; b = a ^ b; a = a ^ b; }
		cout << a << " " << b << "\n";
	}
}

static void copy_array(int *X, int *Y, int n)
{
	for (int i = 0; i < n; ++i) Y[i] = X[i];
}
static void bottom_up_merge(int A[], int iLeft, int iRight, int iEnd, int B[])
{
	int i = iLeft, j = iRight;
	for (int k = iLeft; k < iEnd; k++)
		if (i < iRight && (j >= iEnd || A[i] <= A[j]))
			B[k] = A[i++];
		else
			B[k] = A[j++];
}

#define MIN(a, b) ((a < b) ? a : b)
#define SORT_MAX 75000

int A[SORT_MAX];
int B[SORT_MAX];
int Q1[SORT_MAX];
int Q2[SORT_MAX];

void bottom_up_merge_sort(int *A, /*int **pB, */ int n)
{
	int width, i;
	for (i = 0; i < n; ++i) B[i] = 0;
	for (width = 1; width < n; width = 2 * width) {
		for (i = 0; i < n; i = i + 2 * width)
			bottom_up_merge(A, i, MIN(i + width, n), MIN(i + 2 * width, n), B);
		copy_array(B, A, n);
	}
}

int main()
{
	//generate_input(); return 0;
	//freopen("input.txt", "r", stdin);
	int n, q, k;
	cin >> n >> q >> k;
	//vector<int> A(n);
	//vector<int> Q1(q);
	//vector<int> Q2(q);
	for (int i = 0; i < n; ++i) cin >> A[i];
	for (int i = 0; i < q; ++i) cin >> Q1[i] >> Q2[i];
	for (int i = 0; i < q; ++i) {
		bottom_up_merge_sort(A + Q1[i], Q2[i] - Q1[i] + 1);
	}
	cout << A[k] << "\n";
	return 0;
}

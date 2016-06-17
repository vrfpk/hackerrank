#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "inversions.h"
#define INV_SIZE 100000
void test_merge_sort() {
    int A[INV_SIZE]; // = { 6, 5, 4, 3, 2, 1 };
    // int *B;
    int i;
    long long cnt;
    int n = INV_SIZE;
    freopen("_bcb5c6658381416d19b01bfc1d3993b5_IntegerArray.txt", "r", stdin);
    for (i = 0; i < INV_SIZE; ++i) {
        scanf("%d", &A[i]);
    }
    cnt = bottom_up_merge_sort(A, /*&B,*/ n);
    // printf("test_merge_sort B: %x\n", B);
    // for (i = 0; i < 4; ++i) {
        // printf("%d ", A[i]);
    // }
    printf("answer: %lli\n", cnt);
}

// Driver program to test above function
int main()
{
    test_merge_sort();
	return 0;
}

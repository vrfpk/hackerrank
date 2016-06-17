#include <stdio.h>
#include <malloc.h>
#include "inversions.h"
/*
int inv_count(int A[], int n) {
    int x, y, z;
    if (n == 1)
        return 0;
    else {
        x = inv_count(A, n/2);
        y = inv_count(A+n/2, n/2);
        z = inv_count_split_inv(A, n);
    }
    return x + y + z;
}

int MergeAndCountSplitInv() {
    
}

int SortAndCount(int A[], int n, int *B) {
    int (n == 1)
        return 0;
    else {
        x = SortAndCount(A, n/2);
        y = SortAndCount(A + n/2, n/2);
        z = MergeAndCountSplitInv()
    }
}
*/
static void copy_array(int *X, int *Y, int n) {
    int i;
    // printf("copy_array begins X: %x, Y: %x\n", X, Y);
    for (i = 0; i < n; ++i) {
        Y[i] = X[i];
    }
    // printf("copy_array ends\n");
}
static long long bottom_up_merge(int A[], int iLeft, int iRight, int iEnd, int B[]) {
    int i = iLeft, j = iRight;
    int k;
    long long cnt = 0;
    // printf("bottom_up_merge begins\n");
    //printf("iLeft: %d, iRight: %d, iEnd: %d\n", iLeft, iRight, iEnd);
    for (k = iLeft; k < iEnd; k++) {
        // printf("k: %d, i: %d, j: %d\n", k, i, j);
        if (i < iRight && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i++];
        } else {
            B[k] = A[j++];
            // if ((iRight - i) < 0)
                // printf("iRight - i ! iRight: %d, i: %d\n", iRight, i);
            cnt += (long long) iRight - i;
        }
    }

    //printf("cnt: %d, i: %d, j: %d\n", cnt, i, j);
    // printf("bottom_up_merge ends\n");
    return cnt;
}

#define MIN(a, b) ((a < b) ? a : b)

long long bottom_up_merge_sort(int *A, /*int **pB, */ int n) {
    int width, i;
    long long cnt = 0;
    int *B = (int*) malloc (n * sizeof(int));
    // printf("n: %d, A: %x, B: %x\n", n, A, B);
    for (i = 0; i < n; ++i)
        B[i] = 0;
    
    for (width = 1; width < n; width = 2 * width) {
        // printf("width: %d\n", width);
        for (i = 0; i < n; i = i + 2 * width) {
            cnt += bottom_up_merge(A, i, MIN(i + width, n), MIN(i + 2 * width, n), B);
        }
        //printf("cnt: %lld\n", cnt);
        copy_array(B, A, n);
    }
    // *pB = B;
    free(B);
    if (cnt < 0) {
        printf("cnt < 0, cnt: %d\n", cnt);
    }
    return cnt;
}

static int merge(int A[], int B[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - l;
    int *L = (int*) malloc(n1 * sizeof(n1));
    int *R = (int*) malloc(n2 * sizeof(n1));
    
    return 0;
}



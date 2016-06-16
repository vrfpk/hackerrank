#include <stdio.h>
#include <malloc.h>
#include "algorithms.h"

char* combinations_init_zeros(int n)
{
    int i = 0;
    char *pattern = (char*) malloc(n * sizeof(char));
    while (i < n) pattern[i++] = 0;
    return pattern;
}

void combinations_clear(char* p)
{
    free(p);
}

void combinations_recursive(int set[], char pattern[], int n, int x)
{
    if (x == n - 1) {
        pattern[x] = 0; // last digit, don't select it
        combinations_print(set, pattern, n); // print the set
        pattern[x] = 1; //// last digit, select it
        combinations_print(set, pattern, n);
        return;
    }
    pattern[x] = 0;   //either you will not select this digit
    combinations_recursive(set, pattern, n, x + 1);
    pattern[x] = 1;  //either you will select this digit
    combinations_recursive(set, pattern, n, x + 1);
}

void combinations_non_recursive(int set[], int n)
{
    char overflow = 0;
    char *pattern = combinations_init_zeros(n);
    while (overflow == 0) {
        combinations_print(set, pattern, n);
        overflow = binary_increment(pattern, n);
    }
    combinations_clear(pattern);
}

void combinations_print(int set[], char pattern[], int n)
{
    int i;
    unsigned char isNULL = 0;
    for (i = 0; i < n; ++i) {
        isNULL += pattern[i];
    }
    if (isNULL == 0)
        return;

    isNULL = 1;
    printf("{ ");
    for (i = 0; i < n; i++) {
        if (pattern[i] == 1) {
            printf("%d ", set[i]);
            isNULL = 0;
        }
    }
    if (isNULL) {
        printf("Empty ");
    }
    printf("}\n");
}


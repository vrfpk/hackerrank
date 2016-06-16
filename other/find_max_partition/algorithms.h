#pragma once

#include <stdlib.h>
#include <stdio.h>

/* alloc */

int ** alloc2d(int n, int m);

void free2d(int ** arr);

/* partition */

int find_partion(int arr[], int n);

int find_partion_recursive(int arr[], int n);

/* binary operations */

int binary_increment(char * p, int n);

void binary_xor_assign(char * const left, const char * const right, int n);

void binary_not_assign(char * const left, const char * const right, int n);

int binary_map(char * const p, char * const map, int n);

void binary_unmap(char * const q, char * const r, char * const map, int n);

void binary_copy(char * dst, const char * const src, int n);

void binary_clear(char * const p, int n);

void binary_print(char * A, int n, const char * const intro, const char * const sep);

int binary_sum(const char * const p, const char * const set, int n);

int binary_map_sum(const char * const p, const char * const map, const char * const set, int map_size);

/* combinations */

char * combinations_init_zeros(int n);

void combinations_clear(char * p);

void combinations_recursive(int set[], char pattern[], int n, int x);

void combinations_non_recursive(int set[], int n);

void combinations_print(int set[], char pattern[], int n);

inline int binary_increment(char *p, int n)
{
    int i;
    p[0] += 1;
    for (i = 0; i < n; ++i)
        if (p[i] == 2) {
            p[i] = 0;
            if (i == n - 1)
                return 1; // overflow
            else
                p[i + 1] += 1;
        }
    return 0;
}

inline void binary_xor_assign(char * const left, const char * const right, int n)
{
    int i = 0;
    for (i = 0; i < n; ++i) left[i] = (left[i] != right[i]) ? 1 : 0;
}

inline void binary_not_assign(char * const left, const char * const right, int n)
{
    int i = 0;
    for (i = 0; i < n; ++i) left[i] = (right[i] == 0) ? 1 : 0;
}

inline void binary_map_build(char * const p, int n, char * const map, int *map_size)
{
    int i = 0, k, cnt;
    *map_size = 0;
    for (k = 0; k < n; ++k) if (p[k] == 0) break;
    for (i = 0; i < n; ++i) map[i] = i;
    cnt = k;
    for (i = k; i < n; ++i) {
        if (p[i] != 0) {
            map[cnt] = i;
            p[cnt++] = p[i];
            p[i] = 0;
        }
    }
    for (k = cnt; k < n; ++k) map[k] = -1;
    *map_size = cnt;
}

inline int binary_map(char * const p, char * const map, int n)
{
    int i = 0, cnt = 0;
    for (i = 0; i < n;) {
        if (p[i] != 1) break; // strip trailing "1"s
        map[i++] = -1;
    }
    for (; i < n; ++i) {
        if (p[i] == 0) {
            map[i] = cnt++;
        } else {
            map[i] = -1;
        }
    }
    return cnt;
}

inline void binary_unmap(char * const q, char * const r, char * const map, int n)
{
    int i = 0;
    for (i = 0; i < n; ++i) {
        r[i] = (map[i] != -1) ? q[map[i]] : 0;
    }
}

inline void binary_copy(char * dst, const char * const src, int n)
{
    int i;
    for (i = 0; i < n; ++i) {
        dst[i] = src[i];
    }
}

inline void binary_clear(char * const p, int n)
{
    while (n-- >= 0) p[n] = 0;
}

inline void binary_print(char *A, int n, const char * const intro, const char * const sep)
{
    int i;
    if (intro != NULL)
        printf("%s", intro);
    for (i = 0; i < n; ++i) {
        //for (i = n - 1; i >= 0; i--) {
        printf("%2d", A[i]);
    }
    printf("%s", sep);
}

inline int binary_sum(const char * const p, const char * const set, int n)
{
    int i, sum = 0;
    for (i = 0; i < n; ++i) {
        sum += p[i] * set[i];
    }
    return sum;
}

inline int binary_map_sum(const char * const p, const char * const map, const char * const set, int map_size)
{
    int i, sum = 0;
    for (i = 0; i < map_size; ++i) {
        sum += p[map[i]] * set[map[i]];
    }
    return sum;
}
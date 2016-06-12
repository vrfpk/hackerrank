#ifndef PARTITION_H
#define PARTITION_H

int is_subset_sum_rec(int arr[], int n, int sum);

int find_partition_rec(int arr[], int n);

int **alloc2d(int n, int m);

void free2d(int **p);

int find_partition(int arr[], int n);

int find_max_partition_rec(int arr[], int n);

int find_max_partition(int arr[], int n);

#endif // PARTITION_H

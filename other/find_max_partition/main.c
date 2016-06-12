#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "partition.h"

int main(int argc, char *argv[]) {
    // int n = 6;
    // int p = 0;
    // int i;
    // int arr[] = { 2, 3, 4, 1, 6, 33 };
    
    if (argc < 3)
        return 1;
    int n = atoi(argv[1]);
    int p = 0;
    int i;
    int *arr = (int*) malloc(n * sizeof(int));
    srand(time(NULL));
    for (i = 0; i < n; ++i) {
        arr[i] = rand() % atoi(argv[2]) + 1;
    }
    if (0 == (p = find_max_partition(arr, n)))
        printf("arr cannot be equally devided\n");
    else
        printf("best partition: %d\n", p);
    
    return 0;
}


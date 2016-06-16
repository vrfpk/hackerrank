#include <malloc.h>
#include "algorithms.h"

int **alloc2d(int m, int n)
{
	int *p = (int*) malloc(m * n * sizeof(int));
	int **q = (int**) malloc(m * sizeof(int*));
	int i;
	for (i = 0; i < m; ++i) {
		q[i] = &p[i * n];
	}
	return q;
}

void free2d(int **p)
{
	free(*p);
	free(p);
}


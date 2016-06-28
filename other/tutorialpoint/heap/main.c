#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SWAP(u, v) do { if (u != v) { u = u ^ v; v = u ^ v; u = u ^ v; } } while(0)

#define PARENT(i) (((i) - 1) >> 1)
#define LEFT(i) (((i) << 1) + 1)
#define RIGHT(i) (((i) << 1) + 2)

void add_element(int x, int *heap, /*int *size,*/ int size)
{
	//int c;
    //printf("size: %d, index: %d\n", *size, index);
	//c = index; // (*size)++;
	heap[size] = x;
	while (size != 0 && heap[PARENT(size)] < heap[size]) {
		SWAP(heap[PARENT(size)], heap[size]);
		size = PARENT(size);
	}
}

void output_heap(int *heap, int size)
{
	int cnt, i, j, k, l, m, n, end = 0;
	for (cnt = 0; cnt < 32 && (size >> cnt); ++cnt);

	m = 0;
	k = (1 << cnt);
	for (j = 0; j < cnt && !end; ++j) {
		k >>= 1;
		l = (1 << j);
		n = m;
		while (l--) {
			for (i = 0; i < 2 * k - 1; ++i) printf("  "); printf("+--+");
			if (++n == size) { end = 1; break; }
			for (i = 0; i < 2 * k - 2; ++i) printf("  "); printf("  ");
		}
		printf("\r\n");
		l = (1 << j);
		n = m;
		while (l--) {
			for (i = 0; i < 2 * k - 1; ++i) printf("  "); printf("|%02d|", heap[n]);
			if (++n == size) { end = 1; break; }
			for (i = 0; i < 2 * k - 2; ++i) printf("  "); printf("  ");
		}
		printf("\r\n");
		l = (1 << j);
		while (l--) {
			for (i = 0; i < 2 * k - 1; ++i) printf("  "); printf("+--+");
			if (++m == size) { end = 1; break; }
			for (i = 0; i < 2 * k - 2; ++i) printf("  "); printf("  ");
		}
		printf("\r\n");
		printf("\r\n");
	}
}

void output_array(int *heap, int size)
{
	int i;
	for (i = 0; i < size; ++i) printf("%02d ", heap[i]);
	printf("\n");
}

void remove_root(int *heap, /*int *size,*/ int size)
{
	int c = 0; /*right, left;*/
	//int l;
    
    //printf("size: %d, index: %d\n", *size, index);
	//--(*size);
    //l = size - 1;

	SWAP(heap[c], heap[size-1]);
	//heap[*size] = -1;
	while (1) {
		//right = RIGHT(c);
		//left = LEFT(c);
		if (LEFT(c) >= size-1) {
			break;
		} else if (RIGHT(c) >= size-1) {
			if (heap[LEFT(c)] > heap[c]) 
				SWAP(heap[LEFT(c)], heap[c]);
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

int heap_[30] = { 0 };

int main()
{
	int i;
	int A[15] = { 4, 2, 6 };
	int heap_size = 0;
	srand(2);

	for (i = 0; i < 15; ++i) A[i] = (rand() % 100);

	for (i = 0; i < 15; ++i) {
		add_element(A[i], heap_, /*&heap_size,*/ i);
	}

    //printf("heap_size: %d\n", heap_size);
    
	for (i = 15; i > 0; --i) {
		remove_root(heap_, /*&heap_size,*/ i);
	}
	output_array(heap_, 30);

	return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SWAP(u, v) do { if (u != v) { u = u ^ v; v = u ^ v; u = u ^ v; } } while(0)

#define PARENT(i) (((i) - 1) >> 1)
#define LEFT(i) (((i) << 1) + 1)
#define RIGHT(i) (((i) << 1) + 2)

void add_element(int x, int *heap, int *size)
{
	int c, p;
	c = (*size)++;
	heap[c] = x;
	while (c != 0 && heap[PARENT(c)] < heap[c]) {
		SWAP(heap[PARENT(c)], heap[c]);
		c = PARENT(c);
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

void remove_root(int *heap, int *size)
{
	int current = 0, right, left;
	int q;
	--(*size);

	SWAP(heap[current], heap[*size]);
	//heap[*size] = -1;
	while (1) {
		right = RIGHT(current);
		left = LEFT(current);
		if (left >= *size) {
			break;
		} else if (right >= *size) {
			if (heap[left] > heap[current]) 
				SWAP(heap[left], heap[current]);
			break;
		} else if (heap[left] > heap[right] && heap[left] > heap[current]) {
			SWAP(heap[left], heap[current]);
			current = left;
		} else if (heap[right] >= heap[left] && heap[right] > heap[current]) {
			SWAP(heap[right], heap[current]);
			current = right;
		} else {
			break;
		}
	}
}

int heap_[15];

int main()
{
	int i;
	int A[15] = { 4, 2, 6 };
	int heap_size = 0;
	srand(2);

	for (i = 0; i < 15; ++i) A[i] = (rand() % 100);

	for (i = 0; i < 15; ++i) {
		add_element(A[i], heap_, &heap_size);
	}

	for (i = 0; i < 15; ++i) {
		remove_root(heap_, &heap_size);
	}
	output_array(heap_, 15);

	return 0;
}
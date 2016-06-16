#include "fibonacci.h"

int fib_rec(int n)
{
	if (n <= 1)
		return n;
	return fib_rec(n - 1) + fib_rec(n - 2);
}

#define NIL -1
#define FIB_MAX 100

static int fib_mem_int(int n, int lookup[])
{
	if (lookup[n] == NIL) {
		if (n <= 1) {
			lookup[n] = n;
		} else {
			lookup[n] = fib_mem_int(n - 1, lookup) + fib_mem_int(n - 2, lookup);
		}
	}
	return lookup[n];
}

int fib_mem(int n) {
	int lookup[FIB_MAX];

	int i;
	for (i = 0; i < FIB_MAX; ++i) {
		lookup[i] = NIL;
	}

	return fib_mem_int(n, lookup);
}

int fib_tab(int n)
{
	int i;
	int lookup[FIB_MAX];
	lookup[0] = 0;
	lookup[1] = 1;
	for (i = 2; i <= n; ++i) {
		lookup[i] = lookup[i - 1] + lookup[i - 2];
	}
	return lookup[n];
}
 
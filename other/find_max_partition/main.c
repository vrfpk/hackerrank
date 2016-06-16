#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "algorithms.h"
#include "partition.h"
#include "linked_list.h"
#include "fibonacci.h"
#include "lcs.h"

void test_find_max_partition()
{
	 int n = 6;
	 int p = 0;
	 //int i;
	 int arr[] = { 2, 3, 4, 1, 6, 33 };

	//if (argc < 3)
	//	return 1;
	//int n = atoi(argv[1]);
	//int p = 0;
	//int i;
	//int *arr = (int*) malloc(n * sizeof(int));
	//srand(time(NULL));
	//for (i = 0; i < n; ++i) {
	//	arr[i] = rand() % atoi(argv[2]) + 1;
	//}

	 if (0 == (p = find_max_partition(arr, n)))
		printf("arr cannot be equally devided\n");
	else
		printf("best partition: %d\n", p);
}

void test_linked_list()
{
	int T, data;
	Node *head = NULL;
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &data);
		head = list_insert(head, data);
	}
	list_display(head);
}

void test_fibonacci()
{
	int n = 10;
	printf("Fibonacci number is %d\n", fib_tab(n));
}

void test_lcs()
{
	char X[] = "AGGTAB";
	char Y[] = "GXTXAYB";

	int m = strlen(X);
	int n = strlen(Y);

	printf("Length of LCS is %d\n", lcs_rec(X, m, Y, n));
}

// Driver program to test above function
int main()
{
	test_lcs();

	return 0;
}

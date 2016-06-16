#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

void list_display(Node *head)
{
	Node *start = head;
	while (start) {
		printf("%d ", start->data);
		start = start->next;
	}
}

Node * list_insert(Node * head, int data)
{
	Node **p = &head;

	while (*p != NULL) {
		p = &(*p)->next;
	}

	*p = (Node*) malloc(sizeof(Node));
	(*p)->data = data;
	(*p)->next = NULL;

	return head;
}



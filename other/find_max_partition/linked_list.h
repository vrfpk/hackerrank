#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct Node
{
	int data;
	struct Node* next;
} Node;

void list_display(Node * head);

Node* list_insert(Node *head, int data);

#endif // !LINKED_LIST

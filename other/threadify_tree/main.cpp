#include <stdlib.h>
#include <stdio.h>

#define STACK_MAX 100

typedef struct node
{
	int data;
	int rightThreaded;
	struct node *left;
	struct node *right;
} node;

node* create_node(int d)
{
	node* p = new node;
	p->data = d;
	p->left = p->right = NULL;
	p->rightThreaded = 0;
	return p;
}

void inorder_rec(node *root)
{
	if (root != NULL) {
		inorder_rec(root->left);
		printf("%d ", root->data);
		inorder_rec(root->right);
	}
}

typedef struct stack
{
	node* arr[STACK_MAX];
	int top = -1;
} stack;

int stack_isfull(stack *s)
{
	if (s->top == STACK_MAX)
		return 1;
	return 0;
}

int stack_isempty(stack *s)
{
	if (s->top == -1)
		return 1;
	return 0;
}

int stack_push(stack *s, node* data)
{
	if (!stack_isfull(s)) {
		s->top = s->top + 1;
		s->arr[s->top] = data;
		return 0;
	}
	return -1;
}

node* stack_pop(stack *s)
{
	node* data;
	if (!stack_isempty(s)) {
		data = s->arr[s->top];
		s->top = s->top - 1;
		return data;
	}
	return NULL;
}

void inorder_stack(node *root)
{
	stack *s = new stack;
	node *p = root;

	while (true) {
		while (p != NULL) {
			stack_push(s, p);
			p = p->left;
		}
		if (stack_isempty(s)) {
			delete s;
			return;
		}
		p = stack_pop(s);
		printf("%d ", p->data);
		p = p->right;
	}
}

void revinorder_rec(node *root, node* prev)
{
	if (root != NULL) {
		revinorder_rec(root->right, prev);
		if (root->right == NULL && prev != NULL) {
			root->right = prev;
			root->rightThreaded = 1;
		}
		revinorder_rec(root->left, root);
	}
}

node* tree_leftmost(node* root)
{
	if (root == NULL) {
		return NULL;
	}
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}

void threaded_traverse(node* root)
{
	node* p = tree_leftmost(root);

	while (p != NULL) {
		printf("%d ", p->data);
		if (p->rightThreaded)
			p = p->right;
		else
			p = tree_leftmost(p->right);
	}
}

void tree_convert(node* root)
{
	revinorder_rec(root, NULL);
}

int main()
{
	node *root = create_node(10);
	root->left = create_node(5);
	root->right = create_node(15);
	root->left->left = create_node(1);
	root->left->right = create_node(7);
	root->right->left = create_node(12);
	root->right->right = create_node(20);

	tree_convert(root);
	threaded_traverse(root);
	printf("\n");

	return 0;
}

// COP3502 - CS1 - Fall 2022 - Author: Nicole Nascimento
// headder file for main.c Lab 4

typedef struct node{
	int data;
	struct node *next;
}node;

node*  insert_front(node *root, int item);
node* reverse(node* head);
void insertToPlace(node* list, int val, int place);
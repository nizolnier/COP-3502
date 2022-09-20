#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
  int data;
  struct node* next;
}node;

//this function takes an item and insert it in the linked list pointed by root.
node* insert_front(node* head, int item)
{
    node* temp = (node *)malloc(sizeof(node));
    temp->data = item;
    temp->next = NULL;

    if(head == NULL) {
        head = temp;
    } else {
        temp->next = head;
        head = temp;
    };

    return head;
}

node* insert_sorted(node* root, int item)
{
  node* temp = (node *)malloc(sizeof(node));
  temp->data = item;
  temp->next = NULL;

  if(root == NULL || item < root->data) {
    temp->next = root;
    root = temp;
  } else {
    node *t = root;
    while(t->next != NULL && t->next->data < item) {
        t = t->next;
    }

    temp->next = t->next;
    t->next = temp;
  }
  
  return root;
}


//this function takes an item and insert it in the end of the linked list
node* insert_end(node* root, int item)
{
    node* temp = (node*)malloc(sizeof(node));
    temp->data = item;
    temp->next = NULL;

    if(root == NULL) {
        root = temp;
    } else { // we already have a linked list
        node *t = root;
        while(t->next != NULL) {
            t = t->next;
        }
        // now t is at the last node of the linked list. we are ready to add temp right after t

        t->next = temp;
    }

    return root;
}


/*this function deletes the first occurrence of a given item from linked list.
it returns the updated/original root
*/
node* DelList(node* head, int item)
{
  if(head == NULL)
    return head;
  if(head->data == item) {
    node* temp = head;
    head = head->next;
    free(temp);
    return head;
  }
  // if you are here, it means the item is not in the head

  node* t = head;
  while(t->next && t->next->data != item)
    t = t->next;
  
  if(t->next == NULL) { // item doesnt exist
    return head; 
  }

  // if you are here, t is exactly right before the item
  node* temp = t->next;
  t->next = t->next->next;

  free(temp);

  return head;

}

void display(node* t)
{
  printf("\nPrinting your linked list.......");

  while(t!=NULL)
  {
    printf("%d ", t->data);
    t= t->next;
  }

  printf("\n");	

}

int main()
{	
  //declare root apprpriately
	node *root=NULL; 
    node *t;
	int ch,ele,v, del;
	while(1)
	{
		printf("\nMenu: 1. insert at the front, 2. insert at the end, 3. Delete, 5.  sorted insert 4. exit: ");
	    scanf("%d",&ch);
		if(ch==4)
		{
			printf("\nGOOD BYE>>>>\n");
			break;
		}
		if(ch==1)
		{
			printf("\nEnter data(an integer): ");
			scanf("%d",&ele);

      root = insert_front(root, ele);
      display(root);	

		}
		if(ch==2)
		{
			printf("\nEnter information(an integer): ");
			scanf("%d",&ele);

      root = insert_end(root, ele);
      display(root);
			
		}
	  if(ch==3)
	  {
		  printf("\nEnter info which u want to DELETE: ");
		  scanf("%d",&del);
      
      root = DelList(root, del);
      display(root);	  

		}

    if(ch==5)
		{
			printf("\nEnter data(an integer): ");
			scanf("%d",&ele);

      root = insert_sorted(root, ele);
      display(root);	

		}
	}
  return 0;
}

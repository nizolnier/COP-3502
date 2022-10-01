// practing coding up my own stack with a linked list
#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int data;
    node *next;
} node;

void push(node *head, int val)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = val;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
    } else {
        temp->next = head;
        head = temp;
    }

}

int pop(node *head)
{
    if(head == NULL) {
        printf("stack is empty");
        return -9999;
    } else {
        node* temp = head;

        head = head->next;

        return temp->data;
    }
}

int main(void)
{
    // i dont really feel like coding up a menu
    return 0;
}
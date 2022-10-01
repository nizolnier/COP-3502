// practicing creating my own queue
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
   int data;
   node* next;
} node;

typedef struct queue
{
    node* front;
    node* back;
} queue;

void enQueue(queue* qPtr, int val) {
    node* temp = (node*)malloc(sizeof(node));
    temp->data = val;
    temp->next = NULL;

    if(qPtr->back != NULL) {
        qPtr->back->next = qPtr->back;
    } 

    qPtr->back = temp;
    
    if(qPtr->front == NULL) {
        qPtr->front = temp;
    }
}

int deQueue(queue* qPtr) {
    if(qPtr->front == NULL) {
        return -9999;
    }

    node* temp = qPtr->front;

    qPtr->front = qPtr->front->next;

    return temp->data;    
}


int main(void) {
    // menu goes in here
    return 0;
}

// based on ahmed's lecture
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *prev, *next;
} node;

node *insert_front(node *head, int item)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = item;
    temp->prev = NULL;
    temp->next = head;

    if (head != NULL)
        head->prev = temp;

    head = temp;

    return head;
}

node *insert_end(node *head, int item)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = item;
    temp->next = NULL;

    if (head == NULL)
    {
        temp->prev = head;
        head = temp;
    }
    else
    {
        node *t = head;

        while (t->next != NULL)
            t = t->next;

        t->next = temp;
        temp->prev = t;
    }

    return head;
}

node *delete (node *head, int item)
{
    node *t;
    node *temp;

    if (head == NULL)
        return head;
    if (head->data == item)
    {
        temp = head;
        head = head->next;
        if (head != NULL)
            head->prev = NULL;

        free(temp);

        return head;
    }
    else
    {
        t = head;

        while (t->next != NULL && t->next->data != item)
            t = t->next;

        if (t->next == NULL)
            return head;

        temp = t->next;
        t->next = t->next->next;
        if (t->next)
            t->next->prev = t;

        free(temp);
        return head;
    }
}

int main(void)
{
    return 0;
}

/* COP 3502C Assignment 2
This program is written by: Nicole Nascimento */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -1
#define MAXITEMS 100
#define MAXTIME 1000000000
#define NUMLINES 12

typedef struct customer
{
    char *name;  // name of customer
    int tickets; // num of tickets
    int line;    // line number
    int time;    // time entering line
} customer;

typedef struct node
{
    struct customer *cust;
    struct node *next;
} node;

typedef struct queue
{
    struct node *front;
    struct node *back;
} queue;

customer *createCustomer(int time, char *name, int line, int tickets)
{
    customer *cust = (customer *)malloc(sizeof(customer));

    cust->name = (char *)malloc(sizeof(char) * strlen(name + 1));
    strcpy(cust->name, name);

    cust->time = time;
    cust->line = line;
    cust->tickets = tickets;

    return cust;
}

void init(queue *qPtr)
{
    qPtr->front = NULL;
    qPtr->back = NULL;
}

queue** initQueues()
{
    queue **queues = (queue **)malloc(sizeof(queue *) * NUMLINES);

    for (int i = 0; i < 12; i++)
    {
        queues[i] = (queue *)malloc(sizeof(queue));
        init(queues[i]);
    }

    return queues;
}

int enqueue(queue *qPtr, customer *custom)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->cust = custom;
    temp->next = NULL;

    if (qPtr->back != NULL)
        qPtr->back->next = temp;

    qPtr->back = temp;

    if (qPtr->front == NULL)
        qPtr->front = temp;

    return 1;
}

int dequeue(queue *qPtr);

int empty(queue *qPtr)
{
    return qPtr->front == NULL;
}

customer *peek(queue *qPtr)
{
    if (qPtr->front != NULL)
        return qPtr->front->cust;
    else
        return NULL;
}

int getNext(queue **queues, int curTime)
{
}

int displayQueues(queue **queues)
{
    int res = -1, minTickets = MAXITEMS + 1;
    int ct = 0;
    for (int i = 0; i < NUMLINES; i++)
    {
        if (empty(queues[i]))
        {
            i++;
        }

        customer *temp = peek(queues[i]);

        if (temp->time > ct)
        {
            i++;
        }

        if (temp->tickets < minTickets)
        {
            res = i;
            minTickets = temp->tickets;
        }
    }

    if (res != -1)
        return res;

    int bestTime = MAXTIME + 1;

    for (int i = 0; i < NUMLINES; i++)
    {
        if (empty(queues[i]))
        {
            i++;
        }

        customer *temp = peek(queues[i]);

        if (temp->time < bestTime)
        {
            res = i;
            bestTime = temp->time;
        }

        return res;
    }

    /* for (int i = 0; i < 12; i++)
    {
        node *t = queues[i]->front;

        while (t)
        {
            printf("%s from line %d checks out at time %d\n", t->cust->name, t->cust->line, getTime(t->cust->time, t->cust->tickets));
            t = t->next;
        }
    }*/
}

queue **readInput(queue **queues)
{
    int testCases;
    scanf("%d", &testCases);
    for (int i = 0; i < testCases; i++)
    {
        int customerCount;
        scanf("%d", &customerCount);
        for (int i = 0; i < customerCount; i++)
        {
            int time, line, tickets;
            char name[16];
            scanf("%d %d %s %d", &time, &line, name, &tickets);
            customer *c = createCustomer(time, name, line, tickets);
            enqueue(queues[line - 1], c);
        }
    }

    return queues;
}

int main(void)
{

    queue **myQueues = initQueues();

    myQueues = readInput(myQueues);

    // displayQueues(myQueues);

    return 0;
}
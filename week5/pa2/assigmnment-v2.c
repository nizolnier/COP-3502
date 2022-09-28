/* COP 3502C Assignment 2
This program is written by: Nicole Nascimento */
// pre-processor directives
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leak_detector_c.h"

// constants i will need ;)
#define MAXNAME 16
// maxitems is maximum of tickets
#define MAXITEMS 100
// max time in line
#define MAXTIME 1000000000
// number of lines
#define NUMLINES 12

// structs :)
typedef struct customer
{
    char *name;  // name of customer
    int tickets; // num of tickets
    int line;    // line number
    int time;    // time entering line
} customer;

// node with customer and pointer to next node
typedef struct node
{
    struct customer *cust;
    struct node *next;
} node;

// queue with front and back nodes
typedef struct queue
{
    struct node *front;
    struct node *back;
} queue;

// function that takes a pointer to a queue and initializes it by setting the front and back to null
void init(queue *qPtr)
{
    qPtr->front = NULL;
    qPtr->back = NULL;
}

// function that takes an array of queues and calls the init function for each element
void initQueues(queue *queues)
{
    // for every item in the array of size 12
    for (int i = 0; i < NUMLINES; i++)
    {
        // calling the function and passing the address of the element
        init(&queues[i]);
    }
}

// function that takes a pointer to a queue and a pointer to a customer and inserts the customer in the back of the queue
int enqueue(queue *qPtr, customer *custom)
{
    // creating a temporary node and allocating memory for it
    node *temp = (node *)malloc(sizeof(node));
    // filling temp with data
    temp->cust = custom;
    temp->next = NULL;

    // if the back is not null, i insert the node to the next in back
    if (qPtr->back != NULL)
        qPtr->back->next = temp;

    // and the back becomes temp
    qPtr->back = temp;

    // if the front is null, temp is the front
    if (qPtr->front == NULL)
        qPtr->front = temp;

    return 1;
}

// function that receives a pointer to a queue and returns 0 if it's not empty and 1 if it is empty
int empty(queue *qPtr)
{
    return qPtr->front == NULL;
}

// function that takes a pointer to a queue, "remove the front" and
// i say remove it like that bc you arent actually removing it, you are just hiding it
node *dequeue(queue *qPtr)
{
    // if the queue is empty, just return NULL
    if (empty(qPtr))
        return NULL;

    // save the current front to temp
    node *temp = qPtr->front;

    // move front to next
    qPtr->front = qPtr->front->next;

    // if the front is null, then back it also NULL
    if (qPtr->front == NULL)
    {
        qPtr->back = NULL;
    }

    // return temp
    return temp;
}

// function that receives a pointer to a queue and returns the item in the front or null if the queue is empty
customer *peek(queue *qPtr)
{
    // if the queue is not empty, return the customer
    if (!empty(qPtr))
        return qPtr->front->cust;
    else
        return NULL;
}

// function that takes a node pointer and frees it (from the troubles of life)
void freeNode(node *ptrNode)
{
    // free the name, customer pointer and then the node itself
    free(ptrNode->cust->name);
    free(ptrNode->cust);
    free(ptrNode);
}

// function that receives a customer and does that crazy calculation for the time the customer checks out
// (30 + 5*number of tickets)
int checkoutTime(customer *cust)
{
    return 30 + (5 * cust->tickets);
}

// function that takes 3 integers, one string and creates a dma customer
customer *createCustomer(int time, char *name, int line, int tickets)
{
    // allocating memory for the customer
    customer *cust = (customer *)malloc(sizeof(customer));

    // allocating memory for the name based on the length of the name and then setting the name in customer
    cust->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(cust->name, name);

    // setting the remaining integers
    cust->time = time;
    cust->line = line;
    cust->tickets = tickets;

    // returning our lovely customer
    return cust;
}

// function that receives an array of queues and fills them up with input data
void loadCustomers(queue *lines)
{
    // creating a count for number of customers and scanning it
    int customerCount;
    scanf("%d", &customerCount);

    // for each customer
    for (int i = 0; i < customerCount; i++)
    {
        // create the variables
        int time, line, tickets;
        char name[16];
        // scan and save all of them
        scanf("%d %d %s %d", &time, &line, name, &tickets);
        // call createCustomer and save the return in a variable
        customer *c = createCustomer(time, name, line, tickets);
        // call enqueue with the appropriate queue and customer
        enqueue(&lines[line - 1], c);
    }
}

// function that takes an array of queues and integer for the current time
// and returns the index of the queue that the next customer is in
int getNextCustomer(queue *lines, int curTime)
{
    // setting res as -1 because 0 is a valid index
    // and the minimum tickets as the max+1 because 100 is also possible
    int res = -1, minTickets = MAXITEMS + 1;

    // for each element of the lines
    for (int i = 0; i < NUMLINES; i++)
    {
        // if the current queue is empty, just continue to the next iteration
        if (empty(&lines[i]))
        {
            continue;
        }

        // current customer temp is the peek of the current queue
        customer *tmp = peek(&lines[i]);

        // if the current customer has a time in line that is bigger than current time, i just continue to the next one
        if (tmp->time > curTime)
        {
            continue;
        }

        // if the current customer's tickets is less than the minimum
        if (tmp->tickets < minTickets)
        {
            // res is the index of the line
            res = i;
            // the minimum is now the current customer's tickets
            minTickets = tmp->tickets;
        }
    }

    // if we got a value result just by looping once, we return it
    if (res != -1)
    {
        return res;
    }
    // if not, we need to check the time

    // the best time is the maximum time + 1
    int bestTime = MAXTIME + 1;

    // for each element of the lines
    for (int i = 0; i < NUMLINES; i++)
    {
        // if the queue is empty, just skip it
        if (empty(&lines[i]))
        {
            continue;
        }

        // current customer temp is the peek of the current line
        customer *tmp = peek(&lines[i]);

        // if the time of the customer is less than the current time
        if (tmp->time < bestTime)
        {
            // res is the index of the line
            res = i;
            // best time is now the customer's time
            bestTime = tmp->time;
        }
    }

    // then after all that, we just return the result
    return res;
}

int main(void)
{
    // calling leak detector
    atexit(report_mem_leak);
    // declaring the lines and initializing them by calling the function
    queue lines[12];
    initQueues(lines);

    // scanning the number of test cases
    int testCases;
    scanf("%d", &testCases);

    // for each test case,
    for (int i = 0; i < testCases; i++)
    {
        
        // once they are all set up, i call the loadCustomers function to load queues with customers
        loadCustomers(lines);

        // setting the current time as 0
        int curTime = 0;
        // for each queue,
        for (int j = 0; j < NUMLINES; j++)
        {
            // i get the index of the line of the next customer by calling getNextCustomer
            int index = getNextCustomer(lines, curTime);

            // if the index is negative, i just break the loop
            if (index == -1)
            {
                break;
            }

            // calling dequeue by passing the appropriate queue (based on the index of getNextCustomer) and storing the return
            node *tmp = dequeue(&lines[index]);
            // just to type less (thanks yohan)
            customer *customerTemp = tmp->cust;

            // update the starting time, this will likely be the time of the first customer in each test case
            if (curTime < customerTemp->time)
                curTime = customerTemp->time;

            // add the current time to the checkoutTime of the customer
            curTime += checkoutTime(customerTemp);

            // print the output
            printf("%s from line %d checks out at time %d.\n", customerTemp->name, customerTemp->line, curTime);

            // then free the node
            freeNode(tmp);
        }
    }

    // and that's all :)
    return 0;
}
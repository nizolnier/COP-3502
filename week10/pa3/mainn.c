  /* COP 3502C Programming Assignment 3 
This program is written by: Abrianna Gill */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "leak_detector_c.h"

//stores the (x, y) of the monster and its distance to "me"
typedef struct entity
{
    int x;
    int y;
    int dist;
}entity;

entity me; //global variable to avoid passing it every time 

FILE* ifp;
FILE* ofp;

//data analysis and handling functions
entity* ReadData(int n);
void display(entity* arr, int n);
int compareTo(entity* ptrPt1, entity* ptrPt2);
void queries(entity* monsters, int n, int s);

//sort and search functions
void sortwrapper(entity* monsters, int currsize, int t);
void mergesort(entity* monsters, int left, int right, int t);
void merge(entity* monsters, int left, int mid, int right);
void insertionsort(entity* monsters, int left, int right);
int binsearch(entity* monsters, entity quer, int len);

int main() //gets base information and calls the functions
{
    //leak detector
    atexit(report_mem_leak);
    
    //file i/o 
    ifp = fopen("in1.txt", "r");
    ofp = fopen("out.txt", "w");

    int n, s, t; //number of monsters and queries, threshold
    fscanf(ifp, "%d %d", &me.x, &me.y);
    fscanf(ifp, "%d %d %d", &n, &s, &t);

    //dynamically allocated array of entity structs
    entity* monsters = ReadData(n);

    //passes the array to the sorting functions
    sortwrapper(monsters, n, t);

    //prints the now sorted array to the terminal and file
    display(monsters, n);

    //passes the array and number of monsters and queries to handle the queries
    queries(monsters, n, s);

    //close files and free dma
    fclose(ifp);
    fclose(ofp);
    free(monsters);

    return 0;
}

//returns a dynamically allocated array of monster points and distances from "me" read from a file
entity* ReadData(int n)
{
    entity* monsters = malloc(n * sizeof(entity)); //entity array of size n

    for(int i = 0; i < n; i++)
    {
        //read in coordinates for each monster
        fscanf(ifp, "%d %d", &monsters[i].x, &monsters[i].y);

        //calculate distance from me to each monster (distance formula)
        monsters[i].dist = pow(monsters[i].x - me.x, 2) + pow(monsters[i].y - me.y, 2);
    }

    return monsters;
}

//takes in two entity pointers and compares them; return values are used in sorting and searching functions
int compareTo(entity* ptrPt1, entity* ptrPt2)
{
    //returns a negative if distance 1 < distance 2, positive if d1 > d2
    if(ptrPt1->dist != ptrPt2->dist) return (ptrPt1->dist - ptrPt2->dist);

    //returns a negative if x1 < x2, positive if x1 > x2
    if(ptrPt1->x != ptrPt2->x) return (ptrPt1->x - ptrPt2->x);

    //returns a negative if y1 < y2, positive if y1 > y2
    if(ptrPt1->y != ptrPt2->y) return (ptrPt1->y - ptrPt2->y);

    //if none are true, they are identical points
    return 0;
}

//takes the array, size, and threshold to pass to the right sorting function
void sortwrapper(entity* monsters, int size, int t)
{
    if(size <= t) //if the size of the array is already within the threshold
    {
        insertionsort(monsters, 0, size - 1);
    }

    else
    {
        mergesort(monsters, 0, size - 1, t);
    }
}

//takes the array to sort, left and right index, and threshold (recursive)
void mergesort(entity* monsters, int left, int right, int t)
{
    //if the current (sub)array's size is less than or equal to the threshold
    if(right - left <= t)
    {
        insertionsort(monsters, left, right); //sort using insertion sort
    }
    
    else //divides (sub)array into subarrays to be sorted and then merged
    {
        if(right > left)
        {
            int mid = (left + right) / 2; //middle index

            //recursive splitting by the midpoint
            mergesort(monsters, left, mid, t);
            mergesort(monsters, mid + 1, right, t);

            //combines and sorts the sorted subarrays
            merge(monsters, left, mid, right);
        }
    }
}

//takes the array, left, mid, and right indeces as the sorted subarrays to merge
void merge(entity* monsters, int left, int mid, int right)
{
    //sizes of subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //copies of sorted subarrays
    entity* L = malloc(n1 * sizeof(entity));
    for(int i = 0; i < n1; i++) L[i] = monsters[left + i];

    entity* R = malloc(n2 * sizeof(entity));
    for(int j = 0; j < n2; j++) R[j] = monsters[mid + 1 + j];

    int i = 0, j = 0, k = left; //index trackers

    //copy the sorted subarrays to the original array, smallest element at a time
    while(i < n1 && j < n2)
    {
        int comp = compareTo(&L[i], &R[j]);

        //L[i] comes before R[j]
        if(comp < 0)
        {
            monsters[k] = L[i];
            k++;
            i++;
        }

        //R[j] comes before L[i]
        else
        {
            monsters[k] = R[j];
            k++;
            j++;
        }
    }

    //once one subarray is empty, copy the rest of the other over
    while(i < n1)
    {
        monsters[k] = L[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        monsters[k] = R[j];
        j++;
        k++;
    }

    //free dma
    free(L);
    free(R);
}

//takes the subarray and the left and right indeces to sort
void insertionsort(entity* monsters, int left, int right)
{
    int i, j;
    entity hand;

    //start at the second index and end at the last
    for(i = left + 1; i < right + 1; i++)
    {
        //compare the hand to all the indeces before
        hand = monsters[i];
        for(j = i - 1; j >= left; j--)
        {
            int comp = compareTo(&monsters[j], &hand);

            //shift elements forward as needed
            if(comp > 0) 
            {
                monsters[j + 1] = monsters[j];
            }

            else
                break; //found the correct place for hand
        }

        monsters[j + 1] = hand;
    }
}

//takes the array, size, and number of queries to handle using binary search
void queries(entity* monsters, int n, int s)
{
    for(int i = 0; i < s; i++)
    {
        //read in the query point and calculate distance from "me"
        entity quer;
        fscanf(ifp, "%d %d", &quer.x, &quer.y);
        quer.dist = sqrt(pow(quer.x - me.x, 2) + pow(quer.y - me.y, 2));

        //output the query point
        printf("%d %d ", quer.x, quer.y);
        fprintf(ofp, "%d %d ", quer.x, quer.y);

        //search for that point in the array
        int rank = binsearch(monsters, quer, n);

        if(rank == -1) 
        {
            printf("not found\n");
            fprintf(ofp, "not found\n");
        }

        else
        {
            printf("found at rank %d\n", rank);
            fprintf(ofp, "found at rank %d\n", rank);
        }
    }
}

//takes the array and its size, searches for the entity by splitting the scope each time
int binsearch(entity* monsters, entity quer, int len)
{
    int left = 0, right = len - 1, mid, comp;

    while(left <= right)
    {
        mid = (left + right) / 2; //mid index

        comp = compareTo(&monsters[mid], &quer);

        //entity was found, return index + 1 (rank is one-based)
        if(comp == 0) return mid + 1;
        
        //entity belongs before mid
        else if (comp > 0) right = mid - 1;

        //entity belongs after mid
        else left = mid + 1;
    }
    
    return -1; //entity not present
}

//output the passed array to the terminal and file
void display(entity* arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d %d == dist = %d\n", arr[i].x, arr[i].y, arr[i].dist);
        fprintf(ofp, "%d %d == dist = %d\n", arr[i].x, arr[i].y, arr[i].dist);
    }
}
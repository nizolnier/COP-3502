/* COP 3502C Assignment 3
This program is written by: Nicole Nascimento */
// pre-processors
#include <stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

// structure that contains the coordinates (x,y) and the distance from the initial point
typedef struct point
{
    int x;
    int y;
    int distance;
} point;

// global variable that will hold the initial point
struct point initial;

// functions that i created
int getDistance(int x, int y);
point *readData(int n);
int compareTo(point *p1, point *p2);
void sorting(point *monsters, int n, int t);
void searchQueries(point *monsters, int nMonsters, int sQueries);
// functions that i adapted from Dr. Ahmed
int binarySearch(point monsters[], point query, int n);
void insertionSort(point monsters[], int left, int right);
void merge(point monsters[], int left, int mid, int right);
void printArray(point monsters[], int n);

// driver function
int main(void)
{
    // leak detector report
    atexit(report_mem_leak);
    // variable for # of monsters, # of search queries and threshold
    int nMonsters, sQueries, threshold;

    // scanning all variables :)
    scanf("%d %d %d %d %d", &initial.x, &initial.y, &nMonsters, &sQueries, &threshold);

    // getting my monsters by calling read data
    point *midnightMonsters = readData(nMonsters);

    // sorting these bad boys
    sorting(midnightMonsters, nMonsters, threshold);

    // printing the sorted monsters
    printArray(midnightMonsters, nMonsters);

    // it's time to search the queries!
    searchQueries(midnightMonsters, nMonsters, sQueries);

    // now we set the monsters free to live their lives
    free(midnightMonsters);

    return 0;
}

// function that takes a coordinate (x,y) and calculates the distance from the initial coordinate
// formula = (x1-x2)^2 + (y1-y2)^2, no square roots
int getDistance(int x, int y)
{
    return ((x - initial.x) * (x - initial.x)) + ((y - initial.y) * (y - initial.y));
}

// function that takes an integer n (# of monsters) and allocates memory for them, fills with data and returns filled array
point *readData(int n)
{
    // mallocing
    point *monsters = (point *)malloc(sizeof(point) * n);

    // for each monster
    for (int i = 0; i < n; i++)
    {
        // scan their coordinates
        scanf("%d %d", &monsters[i].x, &monsters[i].y);
        // call getDistance to set the distance int
        monsters[i].distance = getDistance(monsters[i].x, monsters[i].y);
    }

    // return when all monsters are filled
    return monsters;
}

// function that takes two points and compares them
int compareTo(point *p1, point *p2)
{
    // if their distances are different, returns a positive integer if d1 > d2 or negative if d1 < d2
    if (p1->distance != p2->distance)
        return (p1->distance - p2->distance);
    // if their x's are different, returns a positive int if x1 > x2, negative if x1 < x2
    if (p1->x != p2->x)
        return (p1->x - p2->x);
    // if their y's are different, returns a positive int if y1 > y2, negative if y1 < y2
    if (p1->y != p2->y)
        return (p1->y - p2->y);

    // if they are identical it returns 0
    return 0;
}

// function takes the array and its size, searches for the query by splitting the array each time
int binarySearch(point monsters[], point query, int n)
{
    int left = 0, right = n - 1, comp, mid;

    while (left <= right)
    {
        mid = (left + right) / 2;

        comp = compareTo(&monsters[mid], &query);
        // check if item is present at mid
        if (comp == 0)
            return mid + 1;
        // if item greater, ignore left half
        else if (comp < 0)
            left = mid + 1;
        // if item is smaller, ignore right half
        else
            right = mid - 1;
    }
    // if we reach here, then element was not present
    return -1;
}

// function takes the subarray and the left and right indeces to sort
void insertionSort(point monsters[], int left, int right)
{
    int i, j;
    point item;

    // start at the second index and end at the last
    for (i = left + 1; i < right + 1; i++)
    {
        // compare the item to all the indeces before
        item = monsters[i];
        for (j = i - 1; j >= left; j--)
        {
            // shift elements forward as needed
            if (compareTo(&monsters[j], &item) > 0)
                monsters[j + 1] = monsters[j];
            else
                break; // found the correct place for item
        }
        monsters[j + 1] = item;
    }
}

// function that takes the array, left, mid, and right indeces as the sorted subarrays to merge
void merge(point monsters[], int left, int mid, int right)
{
    int i, j, k;
    // sizes of subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // create temp arrays
    point *L = (point *)malloc(n1 * sizeof(point));
    point *R = (point *)malloc(n2 * sizeof(point));

    // copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = monsters[left + i];
    for (j = 0; j < n2; j++)
        R[j] = monsters[mid + 1 + j];

    // merge the temp arrays back into arr[l..r]
    i = 0;    // initial index of first subarray
    j = 0;    // initial index of second subarray
    k = left; // initial index of merged subarray
    while (i < n1 && j < n2)
    {
        // L[i] comes before R[j]
        if (compareTo(&L[i], &R[j]) < 0)
        {
            monsters[k] = L[i];
            i++;
        }
        // R[j] comes before L[i]
        else
        {
            monsters[k] = R[j];
            j++;
        }
        k++;
    }

    // copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        monsters[k] = L[i];
        i++;
        k++;
    }

    // copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        monsters[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

// takes the array to sort, left and right index, and threshold (recursive)
void mergeSort(point monsters[], int left, int right, int threshold)
{
    // if the current (sub)array's size is less than or equal to the threshold, use insertionSort
    if (right - left <= threshold)
        insertionSort(monsters, left, right);
    else // divides (sub)array into subarrays to be sorted and then merged
    {
        if (right > left)
        {
            // get the mid point
            int mid = (left + right) / 2;

            // sort first and second halves
            mergeSort(monsters, left, mid, threshold);
            mergeSort(monsters, mid + 1, right, threshold);

            // merge them
            merge(monsters, left, mid, right);
        }
    }
}

// function that takes an array of points and the size of the array and prints it to console and file
void printArray(point monsters[], int n)
{
    int i;
    // for each monster
    for (i = 0; i < n; i++)
    {
        // print the coordinates to the file
        printf("%d %d\n", monsters[i].x, monsters[i].y);
        // print the coordinates to console
        fprintf(stderr, "%d %d\n", monsters[i].x, monsters[i].y);
    }
}

// function that takes array of points, size of array and threshold and decides which sorting strategy is more appropriate
void sorting(point *monsters, int n, int t)
{
    // if size is less than or equal to threshold, use insertionSort
    if (n <= t)
    {
        insertionSort(monsters, 0, n - 1);
    }
    // if not, use mergeSort
    else
    {
        mergeSort(monsters, 0, n - 1, t);
    }
}

// function that takes an array of points, size of it and number of queries
// it does a binary search on the array for each query and displays the result
void searchQueries(point *monsters, int nMonsters, int sQueries)
{
    // temp point for the query
    point temp;
    // for each query,
    for (int i = 0; i < sQueries; i++)
    {
        // scan the coordinates
        scanf("%d %d", &temp.x, &temp.y);
        // calculate the distance
        temp.distance = getDistance(temp.x, temp.y);
        // get the rank by doing a binary search
        int rank = binarySearch(monsters, temp, nMonsters);

        // if rank is -1, monster was not found
        if (rank == -1)
        {
            printf("%d %d not found\n", temp.x, temp.y);
            fprintf(stderr, "%d %d not found\n", temp.x, temp.y);
        }
        // if not, print the rank
        else
        {
            printf("%d %d found at rank %d\n", temp.x, temp.y, rank);
            fprintf(stderr, "%d %d found at rank %d\n", temp.x, temp.y, rank);
        }
    }
}

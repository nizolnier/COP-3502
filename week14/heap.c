// Arup Guha
// 2/27/08
// Example of a heap data structure implementation for COP 3502
// Edited on 4/12/2016

// Tanvir Ahmed: Some methods and array size were changed for demonstration purpose.


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 100
#define NUM_TEST_INSERTS 150
//#define NUM_TEST_INSERTS 1000000
#define NUM_TOTAL_OPS 10000000
#define PRINT 0

struct heapStruct {
    int* heaparray;
    int capacity;
    int size;
};

// Used to create a heap.
struct heapStruct *initHeap();
struct heapStruct * initHeapfromArray(int* values, int length);
void heapify(struct heapStruct *h);

// Helper functions.
void percolateDown(struct heapStruct *h, int index);
void percolateUp(struct heapStruct *h, int index);
int insert(struct heapStruct *h, int value);

// Two key functions to implement priority queue.
int removeMin(struct heapStruct *h);
void printHeap(struct heapStruct *h);

// More helper functions.
void swap(struct heapStruct *h, int index1, int index2);
int minimum(int a, int indexa, int b, int indexb);
void freeHeap(struct heapStruct *h);

// Runs a heap sort.
void sort(int values[], int length);

int main() {
    int item;

    // Set up heap and random number generator.
    srand(time(0));
    struct heapStruct *heapPtr;
    heapPtr = initHeap();

    // Insert a bunch of random items.
    int i;
    for (i=0; i<NUM_TEST_INSERTS; i++) {
        item = rand()%1000;
        int outcome = insert(heapPtr, item);
        if (!outcome) break;

    }

    printf("Printing the heap array\n");
    printHeap(heapPtr);

    // Pull them out in sorted order.
    int* sorted = (int*)malloc(sizeof(int)*heapPtr->size);
    for (i=0; heapPtr->size>0; i++)
        sorted[i] = removeMin(heapPtr); //remove and return the min item from the heap

    //printing the sorted data. The following loop should be commented if you have a very large data set
    printf("\nPrinting the sorted data: \n");
    for (i=0; i<NUM_TEST_INSERTS-1; i++)
        printf("%d ", sorted[i]);

    // Check if it's really sorted. It can be useful for very large data set as printing them in the screen will not be feasible in that case.
    int isSorted = 1;
    for (i=0; i<NUM_TEST_INSERTS-1; i++)
        if (sorted[i] > sorted[i+1])
            isSorted = 0;
    if (isSorted) printf("\n We have checked and found that the  Array is sorted!\n");

    //now our heap is already empty. However, we have all the data in the array called sorted. Let's rebuild it

   // Clean up.
    free(sorted);
    freeHeap(heapPtr);

    //generating a random array for generating a heap using heapify
    int* randArray = (int*)malloc(sizeof(int)*NUM_TEST_INSERTS);
    for (i=0; i<NUM_TEST_INSERTS; i++) {
        randArray[i] = rand()%1000;
    }

    heapPtr = initHeapfromArray(randArray,NUM_TEST_INSERTS-1);

    printf("\nPrinting the heap array after generating from the random array\n");
    printHeap(heapPtr);
    // Clean up.
    free(randArray);
    freeHeap(heapPtr);

    return 0;
}

// Initialize an empty heap with a capacity of SIZE.
struct heapStruct* initHeap() {

    struct heapStruct* h;

    // Allocate space for the heap and set the size for an empty heap.
    h = (struct heapStruct*)(malloc(sizeof(struct heapStruct)));
    h->capacity = SIZE;
    h->heaparray = (int*)malloc(sizeof(int)*(SIZE+1));
    h->size = 0;
    return h;
}

// Frees the struct pointed to by h.
void freeHeap(struct heapStruct *h) {
     free(h->heaparray);
     free(h);
}

// Initializes the heap using the first length number of items in the array
// values.
struct heapStruct * initHeapfromArray(int* values, int length) {

    int i;
    struct heapStruct* h;

    h = (struct heapStruct*)(malloc(sizeof(struct heapStruct)));
    // We allocate one extra slot, since slot 0 stays unused.
    h->heaparray = (int*)malloc(sizeof(int)*(length+1));

    // Just copy the values into our array.
    for (i=1; i<=length; i++)
        h->heaparray[i] = values[i-1];

    // This is the number of values we copied.
    h->size = length;

    // This takes our random values and rearranges them into a heap.
    heapify(h);
    return h;
}

// h points to a heap structure that has values inside of it, but isn't yet
// organized into a heap and does exactly that.
void heapify(struct heapStruct *h) {

    int i;

    // We form a heap by just running percolateDown on the first half of the
    // elements, in reverse order.
    for (i=h->size/2; i>0; i--)
        percolateDown(h, i);

}

// Runs percolate down on the heap pointed to by h on the node stored in index.
void percolateDown(struct heapStruct *h, int index) {

    int min;

    // Only try to percolate down internal nodes.
    if ((2*index+1) <= h->size) {

        // Find the minimum value of the two children of this node.
        min = minimum(h->heaparray[2*index], 2*index, h->heaparray[2*index+1], 2*index+1);

      // If this value is less than the current value, then we need to move
      // our current value down the heap.
        if (h->heaparray[index] > h->heaparray[min]) {
            swap(h, index, min);

            // This part is recursive and allows us to continue percolating
            // down the element in question.
            percolateDown(h, min);
        }
    }

    // Case where our current element has exactly one child, a left child.
    else if (h->size == 2*index) {

        // Here we only compare the current item to its only child.
        // Clearly, no recursive call is needed since the child of this node
        // is a leaf.
        if (h->heaparray[index] > h->heaparray[2*index])
            swap(h, index, 2*index);
    }
}

// Runs percolate up on the heap pointed to by h on the node stored in index.
void percolateUp(struct heapStruct *h, int index) {

    // Can only percolate up if the node isn't the root.
    if (index > 1) {

        // See if our current node is smaller in value than its parent.
        if (h->heaparray[index/2] > h->heaparray[index]) {

            // Move our node up one level.
            swap(h, index, index/2);

            // See if it needs to be done again.
            percolateUp(h, index/2);
        }
    }
}

// Inserts value into the heap pointed to by h. Returns 1 if the insert was
// successful, 0 otherwise.
int insert(struct heapStruct *h, int value) {

    int* temp;
    int* throwaway;
    int i;

    // Our array is full, we need to allocate some new space!
    if (h->size == h->capacity) {

        // Allocate new space for an array.
        h->heaparray = (int*)realloc(h->heaparray, sizeof(int)*(2*h->capacity+1));

        // Realloc failed so we quit.
        if (h->heaparray == NULL) return 0;

        // Double the capacity.
        h->capacity *= 2;
    }

    // Adjust all the necessary components of h, and then move the inserted
    // item into its appropriate location.
    h->size++;
    h->heaparray[h->size] = value;
    percolateUp(h, h->size);
}

int removeMin(struct heapStruct *h) {

    int retval;

    // We can only remove an element, if one exists in the heap!
    if (h->size > 0) {

        // This is where the minimum is stored.
        retval = h->heaparray[1];

        // Copy the last value into this top slot.
        h->heaparray[1] = h->heaparray[h->size];

        // Our heap will have one fewer items.
        h->size--;

        // Need to let this value move down to its rightful spot in the heap.
        percolateDown(h, 1);

        // Now we can return our value.
        return retval;
    }

    // No value to return, indicate failure with a -1.
    else
        return -1;
}

// For debugging purposes, lets us see what's in the heap.
void printHeap(struct heapStruct *h) {
    int i;

    for (i=1; i<=h->size; i++)
        printf("%d ", h->heaparray[i]);
    printf("\n");
}

// Swaps the values stored in the heap pointed to by h in index1 and index2.
void swap(struct heapStruct *h, int index1, int index2) {
    int temp = h->heaparray[index1];
    h->heaparray[index1] = h->heaparray[index2];
    h->heaparray[index2] = temp;
}

// Returns indexa if a < b, and returns indexb otherwise.
int minimum(int a, int indexa, int b, int indexb) {

    // Return the value associated with a.
    if (a < b)
        return indexa;

    // Return the value associated with b.
    else
        return indexb;
}

// Runs a heap sort by creating a heap out of the values in the array, and then
// extracting those values one-by-one from the heap back into the array in the
// proper order.
void sort(int values[], int length) {

     struct heapStruct *h;
     int i;

     // Create a heap from the array of values.
     h =  initHeapfromArray(values, length);
     length = h->size;

     // Remove these values from the heap one by one and store them back in the
     // original array.
     for (i=0; i<length; i++) {
         values[i] = removeMin(h);
     }
}

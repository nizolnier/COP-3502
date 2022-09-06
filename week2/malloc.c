#include <stdio.h>

void main() {
    int *ptr1 = (int *)malloc(10 * sizeof(int)); // why are we casting? malloc returns void pointer
    int *ptr2;
    int i;
    if (ptr1 == NULL) {
        printf("Could not allocate memory\n");
        exit(-1);
    } else {
        printf("Memory allocated. Printing data: \n");
        for(i=0; i<10; i++)
            printf("%d ", ptr1[i]); // do not use *(ptr + i), it gets too complicated
        // it will print garbage values
    }
    
    ptr2 = (int *)calloc(10, sizeof(int));
    
    if (ptr2 == NULL) { 
        printf("Could not allocate memory\n");
        exit(-1);
    } else {
        printf("Memory allocated. Printing data after calloc: \n");
        for(i=0; i<10; i++) {
            printf("%d ", ptr2[i]);
            // it will print 0 for all elements
        }
    }
    free(ptr1);
    free(ptr2);
}
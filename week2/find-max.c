#include <stdio.h>
#include <stdlib.h>

int *readArray(int size)
{
    int *p = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        scanf("%d", &p[i]);
    return p;
}
int findMax(int arr[], int len)
{
    int i, max = arr[0];
    for (i = 1; i < len; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
int main(void)
{
    int size;
    int *myarr;
    printf("How many numbers? ");
    scanf("%d", &size);
    myarr = readArray(size);
    printf("Printing the array from main function: ");
    for (int i = 0; i < size; i++)
        printf("%d ", myarr[i]);
    printf("\nThe max number in the array is %d", findMax(myarr, size));
    free(myarr); // free the memory
    return 0;
}
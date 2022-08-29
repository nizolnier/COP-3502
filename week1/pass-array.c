#include <stdio.h>

void incBy2(int *A, int n) // also can be written as: incBy2(int A[], int n) or incBy2(int A[6], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        // even A is a pointer, you can write it like an array as you have passed an array here
        A[i] = A[i] + 2;
    }
}

int main()
{
    int num[] = {24, 34, 12, 44, 56, 17};
    int i;
    printf("Original Array: ");
    for (i = 0; i < 6; i++)
        printf("%d ", num[i]);
    incBy2(num, 6);
    printf("\nArray after calling incBy2: ");
    for (i = 0; i < 6; i++)
        printf("%d ", num[i]);
}

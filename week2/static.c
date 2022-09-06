#include <stdio.h>

int data(int a, int b)
{
    int sum = 0, A[10];
    for (int i = 0; i < 10; i++)
    {
        A[i] = a * b * i;
        sum = sum + A[i];
        printf("%d", A[i]);
    }
    return sum;
    // also remember that we cannot return this statically declared array from function

    // the array, a, b and sum will be destroyed after the function is processed
}
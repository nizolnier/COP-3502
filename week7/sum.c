#include <stdio.h>

// Pre-condition: n is a positive integer.
// Post-condition: Function returns the sum 1+2+...+n
int Triangle_Number(int n)
{
    int index, sum = 0;
    for (index = 1; index <= n; index++)
        sum = sum + index;
    return sum;
}

// Pre-condition: n is a positive integer.
// Post-condition: Function returns the sum 1+2+...+n
int Triangle_Number(int n)
{
    if (n == 0)
        return 0;
    else
        return (n + Triangle_Number(n - 1));
}
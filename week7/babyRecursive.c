#include <stdio.h>

void ascending(int x)
{
    if (x == 0)
        return; // this breaking condition will result in poping the function call stack

    ascending(x - 1);
    printf("%d ", x); // this line (including the value of x) is kept in the stack for each call of rec(x-1) in the above line
}

void decending(int x)
{
    if (x == 0)
        return;       // breaking condition
    printf("%d ", x); // prints first then recursion
    decending(x - 1);
}

int main()
{
    printf("Calling decending: ");
    decending(10);
    printf("\nCalling ascending: ");
    ascending(10);
}
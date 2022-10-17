#include <stdio.h>

int fact(int n);
int main(void)
{
    int factorial = fact(10);
    printf("%d\n", factorial);
    return 0;
}
// Here’s the Fact Function
int fact(int n)
{
    if (n == 0)
        return 1;
    else
        return (n * Fact(n - 1));
}

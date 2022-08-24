#include <stdio.h>

int main(void) {
    int x, y;
    int *p1, *p2;
    x = -42;
    y = 163;
    p1 = &x;
    p2 = &y;
    printf("p1 = %p *p1 = %d \n", p1, *p1);
    printf("p2 = %p *p2 = %d \n", p2, *p2);
    printf("---------\n");
    *p1 = 17; // dereferencing. It means put 17 to the address where p1 is pointing to.
    // Kind of x = 17 printf("p1 = %p *p1 = %d \n", p1, *p1);
    printf("---------\n");
    p1 = p2; // p1 is not pointing to x anymore. Now pointing to y
    printf("p1 = %p *p1 = %d \n", p1, *p1);
    printf("---------\n");
    p2 = &x;
    printf("---------\n");
    printf("p2 = %p *p2 = %d \n", p2, *p2);
    *p1 = *p2;
    printf("p1 = %p *p1 = %d \n", p1, *p1);
    printf("---------");
    return 0;
}

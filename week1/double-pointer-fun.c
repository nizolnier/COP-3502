#include <stdio.h>


void funV1(int *p) {
    p = NULL;
}

void funV2(int **p) {
    *p = NULL;
}

int main(void) {
    int a = 10, b = 20, *p1, **p2;

    p1 = &a;

    printf("address of a is %p\n", &a);
    printf("p1 is %p\n", p1);
    printf("address of p1 is %p\n", &p1);

    funV1(p1);

    printf("p1 is %p\n", p1);

    funV2(&p1);

    printf("p1 is %p\n", p1);

}
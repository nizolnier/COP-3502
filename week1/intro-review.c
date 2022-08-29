#include <stdio.h>

int main(void) {
    int a = 5;
    int *b = &a;

    printf("size of a is %d\n", sizeof(a));

    printf("address of a is %p\n", &a);
    printf("b is %p\n", b);

    printf("*b is %d\n", *b);
    printf("b is %p\n", b);

    printf("size of b is %u\n", sizeof(b));

    return 0;
}

// *(address) == value
// address == &value
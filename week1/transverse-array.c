#include <stdio.h>

int main()
{
    int data[] = {87, 99, 75, 88, 93};
    int *p;
    int i;
    for (i = 0; i < 5; i++)
        printf("address: %p, value: %d, test: %d\n", data + i,
               *(data + i), *data + i);
    printf("--------using p-------------\n");
    p = data; // p is now &data[0]
    for (i = 0; i < 5; i++)
    {
        printf("address: %p, value: %d \n", p, *p);
        p++;
    }
    return 0;
}

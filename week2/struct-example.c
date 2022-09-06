#include <stdio.h>
#include <stdlib.h>

struct point
{
    int x;
    int y;
};
struct point *createRandPoints(int size, int maxVal)
{
    struct point *temp;
    temp = (struct point *)malloc(size * sizeof(struct point));
    int i;
    for (i = 0; i < size; i++)
    {
        temp[i].x = 1 + rand() % maxVal;
        temp[i].y = 1 + rand() % maxVal;
    }
    return temp;
}
int main(void)
{
    struct point *p;
    int size;
    printf("How many points? ");
    scanf("%d", &size);
    p = createRandPoints(size, 100);
    printf("Printing the random points: \n");
    for (int i = 0; i < size; i++)
    {
        printf("point %d, x = %d, y = %d\n", i, p[i].x, p[i].y);
    }
    free(p);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
typedef struct point
{
    int x;
    int y;
} point;
point *createPoint()
{
    point *temp;
    temp = (point *)malloc(sizeof(struct point));
    scanf("%d %d", &(temp->x), &(temp->y));
    return temp;
}
int main(void)
{
    point *p;
    p = createPoint();
    printf("point in main %d %d", p->x, p->y);
    free(p);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct point
{
    int x;
    int y;
};

struct point **createRandPoints(int size, int maxVal)
{
    struct point **temp;
    temp = (struct point **)malloc(size * sizeof(struct point *));
    int i;
    for (i = 0; i < size; i++)
    {
        temp[i] = (struct point *)malloc(sizeof(struct point));
        temp[i]->x = 1 + rand() % maxVal;
        temp[i]->y = 1 + rand() % maxVal;
    }
    return temp;
}

// notice the double pointer – the first is for the array, the second is for the contents of each array element
int main(void) {
    struct point **my_pts = createRandPoints(100,
                                             1000);
    // Do something with my_pts.
    // Frees each individual point pointer.
    int i;
    for (i = 0; i < 100; i++)
        free(my_pts[i]);
    // Frees the memory that stores the main array.
    free(my_pts);

    return 0;
}
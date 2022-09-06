#include <stdio.h>
#include <time.h>
#define EXTRA 10
int main()
{
    int numVals;
    srand(time(0));
    printf("How many numbers?\n");
    scanf("%d", &numVals);
    int *values = (int *)malloc(numVals * sizeof(int));
    int i;
    for (i = 0; i < numVals; i++)
        values[i] = rand() % 100;
    for (i = 0; i < numVals; i++)
        printf("%d ", values[i]);
    printf("\n")
    values = (int *)realloc(values, (numVals + EXTRA) * sizeof(int));
    for (i = 0; i < EXTRA; i++)
        values[i + numVals] =
            rand() % 100;
    numVals += EXTRA;
    for (i = 0; i < numVals; i++)
        printf("%d ", values[i]);
        
    printf("\n");
    free(values);
    return 0;
}
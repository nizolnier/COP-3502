#include <stdio.h>
#include <stdlib.h>

float ** AllocateArrayOfArrays( int P, int *Lengths) {
    float ** bigArray = (float **)malloc(P*sizeof(float));

    for(int i = 0; i < P; i++) {
        bigArray[i] = (float *)malloc(Lengths[i]*sizeof(float));

        for(int j = 0; j < Lengths[i]; j++) {
            bigArray[i][j] = 1 + rand()%100;

            printf("%f\n", bigArray[i][j]);
        }
    }

    return bigArray;
}

int main(void) {
    int lengths[] = {5,4,3,2};
    int p = 4;

    float ** bigBig = AllocateArrayOfArrays(p, lengths);

    for(int i = 0; i < p; i++) {
        free(bigBig[i]);
    }

    free(bigBig);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct BigInteger
{
    int *digits;
    int size;
};

struct BigInteger *createRandBigInt(int numDigits)
{
    struct integer *temp;
    temp = (struct BigInteger *)malloc(sizeof(struct BigInteger));
    temp->digits = (int *)malloc(numDigits * sizeof(int));
    temp->size = numDigits;
    temp->digits[numDigits - 1] = 1 + rand() % 9; // we just want last digit to be nonzero
    int i;
    for (i = 0; i < numDigits - 1; i++)
        temp->digits[i] = rand() % 10;
    return temp;
}

// Nicole Nascimento - Heap Lab
#include <stdio.h>
#include "main.h"

/* How many entries? 6
Enter 6 entries: 12 13 14 15 110 115
Recursive says Yes!
Iterative says Yes! */

int main()
{
    int size = 0;
    printf("How many entries? ");
    scanf("%d", &size);
    printf("Enter %d entries: ", size);

    int arr[size];
    for(int i = 0; i < size; i++) {
        scanf("%d ", &arr[i]);
    }

    isHeap_recursive(arr, 0, size) ? printf("Recursive says Yes!\n") : printf("Recursive says No!\n");
    isHeap_iter(arr, size) ? printf("Iterative says Yes!\n") : printf("Iterative says No!\n");
}

int isHeap_iter(int arr[], int n)
{
    for (int i = 0; i <= (n - 2) / 2; i++)
    {
        if (arr[i * 2 + 1] < arr[i])
        {
            return 0;
        }
        else if (2 * i + 2 < n && arr[2 * i + 2] < arr[i])
        {
            return 0;
        }
    }
    return 1;
}

int isHeap_recursive(int arr[], int i, int n)
{
    if (i >= n || n <= 0)
    {
        return 1;
    }
    if ((2 * i + 1) < n)
    {
        if (arr[2 * i + 1] < arr[i])
        {
            return 0;
        }
    }
    if ((2 * i + 2) < n)
    {
        if (arr[2 * i + 2] < arr[i])
        {
            return 0;
        }
    }
    return (isHeap_recursive(arr, i * 2 + 1, n)) && (isHeap_recursive(arr, 2 * i + 2, n));
}
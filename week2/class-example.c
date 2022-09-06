#include <stdio.h>
#include <stdlib.h>

int* arrayFactory(int length) {
    int* manager = (int *)malloc(length * sizeof(int));

    for(int i=0; i < length; i++) {
        manager[i] = 1 + rand()%100; // 1 - 100
    }

    return manager; // manager dead after function
    // but the memory is still there and going to you
}

void display(int* a, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
}

int main(void) {
    int n;
    scanf("%d", &n);

    int* you = arrayFactory(n);

    display(you, n);

    free(you);

    you = arrayFactory(10);
    
    return 0;
}
int *readArray(int size) {
    int *p1 = (int *)malloc(size * sizeof(int));
    int *p2 = (int *)malloc(size * sizeof(int));
    for (i = 0; i < size; i++)
        scanf("%d", &p1[i]);
    p2 = p1;
    return p1;
}

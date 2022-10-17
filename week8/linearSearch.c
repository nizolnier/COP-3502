int linearSearch(int array[], int len, int value)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (array[i] == value)
            return 1;
    }
    return 0;
}
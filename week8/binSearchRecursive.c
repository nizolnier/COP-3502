int binSearch(int *values, int low, int high, int searchval)
{
    int mid;
    if (low <= high)
    {
        mid = (low + high) / 2;
        if (searchval < values[mid])
            return binSearch(values, low, mid - 1, searchval);
        else if (searchval > values[mid])
            return binSearch(values, mid + 1, high, searchval);
        else
            return 1;
    }
    return 0;
}
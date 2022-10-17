int binarySearch(int list[], int item, int len)
{
    int l = 0, h = len - 1;
    int mid;
    while (l <= h)
    {
        mid = (l + h) / 2;
        // Check if item is present at mid
        if (list[mid] == item)
            return mid;
        // If item greater, ignore left half
        if (list[mid] < item)
            l = mid + 1;
        // If item is smaller, ignore right half
        else
            h = mid - 1;
    }
    // if we reach here, then element was
    // not present
    return -1;
}
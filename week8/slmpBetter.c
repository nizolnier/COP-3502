void slmp(int list1[], int n, int list2[], int m)
{
    int i = 0, j = 0;
    // Go while we still have numbers in both lists.
    while (i < n && j < m)
    {
        // Safe to advance list 1 pointer.
        if (list1[i] < list2[j])
            i++;
        // Safe to advance list 2 pointer.
        else if (list2[j] < list1[i])
            j++;
        // Match!
        else
        {
            printf("%d ", list1[i]);
            i++;
            j++;
        }
    }
}
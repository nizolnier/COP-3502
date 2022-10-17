void printMatches(int list1[], int list2[], int len1, int len2)
{
    int i, j;
    for (i = 0; i < len1; i++)
    {
        for (j = 0; j < len2; j++) // linear search
        {
            if (list1[i] == list2[j])
            {
                printf("%d", list1[i]);
                break;
            }
        }
    }
}
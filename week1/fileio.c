#include <stdio.h>
/*this simple program read data from a text file input1.txt.
The first line of the file contains number of items (N)
and then the program reads next N items into an array.
After reading, the program shows the data in console and
also write the data in reverse order in output1.txt file */
int main()
{
    int *p, size, i;
    FILE *fp, *outfp;
    // Open the input file.
    fp = fopen("input1.txt", "r");
    outfp = fopen("output1.txt", "w");
    // Read in all the numbers into the array.
    fscanf(fp, "%d", &size);
    p = (int *)malloc(size * sizeof(int));
    for (i = 0; i < size; i++)
    {
        fscanf(fp, "%d", &p[i]);
    }
    // Print out the array elements backwards.
    for (i = size - 1; i >= 0; i--)
    {
        printf("%d\n", p[i]);
        fprintf(outfp, "%d\n", p[i]);
    }
    printf("Output written to output1.txt");
    // Close the file and free memory.
    free(p);
    fclose(fp);
    fclose(outfp);
    return 0;
}
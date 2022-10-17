// This program prints all the permutation of a string
#include <stdio.h>
#include <string.h>

/* swap function*/
void swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/* This function prints the permutation of a string
   This function takes three parameters:
   String, starting index, and ending index*/
void permute(char *s, int l, int r)
{
   int i;
   if (l == r)
     printf("%s\n", s);
   else
   {
       for (i = l; i <= r; i++)
       {
          swap(&s[l], &s[i]);
          permute(s, l+1, r);
          swap(&s[l], &s[i]); //swap back
       }
   }
}

int main()
{
    char str[] = "CAT";
    int n = strlen(str);
    permute(str, 0, n-1);
    return 0;
}

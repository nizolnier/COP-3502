#include <stdio.h>
int main () {
   FILE * infile;
   FILE * outfile;
   int student_ID,j,g1,g2,g3;
   infile  = fopen(  "students.txt",   "r" );
   outfile = fopen( "new.txt" , "w");
   for (j =1; j <= 5; j++)
     {
        fscanf( infile, "%d", &student_ID);
        fscanf( infile," %d %d %d ",  &g1, &g2, &g3);
        g1 = g1 + 10;
        g2 = g2 + 10;
        g3 = g3 + 10;
        printf("%d %d %d %d\n", student_ID, g1, g2,g3);
        fprintf(outfile,"%d %d %d  %d \n", student_ID, g1,g2,g3); 
     }
   fclose(infile); // Close both files.
   fclose(outfile);
   system("PAUSE");
   return 0;
}
#include <stdio.h>
#define SIZE 10


void display_grid(char grid[][SIZE], int r, int c)
{
  for(int i=0; i<r; i++)
  {
    for(int j=0; j<c; j++)
    {
      printf("%c", grid[i][j]);

    }
    printf("\n");
  }

}

void flood_fill_rec(char grid[][SIZE], int x, int y, char new_ch, char old_ch)
{
  if(x<0 || y<0 || x>=SIZE || y >=SIZE) //if it is out of the matrix
    return;
  if(grid[x][y] !=  old_ch) //if it is not the old char, no need to go to other direction for that cell
    return;
    
  grid[x][y] = new_ch;
  flood_fill_rec(grid, x+1, y, new_ch, old_ch);
  flood_fill_rec(grid, x-1, y, new_ch, old_ch);
  flood_fill_rec(grid, x, y+1, new_ch, old_ch);
  flood_fill_rec(grid, x, y-1, new_ch, old_ch);

}


void flood_fill(char grid[][SIZE], int x, int y, char ch)
{
  char old_char  = grid[x][y];
  flood_fill_rec(grid, x, y, ch, old_char);

}

int main(void) {
  
  char grid[SIZE][SIZE] = {
    {'*', '*','*','*','*','*','*','*','*','*'},
    {'*', '*',' ' , ' ', '*', '*', '*',' ', ' ', '*'},
    {'*', ' ',' ' , ' ', '*', '*', ' ',' ', ' ', '*'},
    {'*', ' ',' ' , ' ', ' ', '*', ' ',' ', ' ', '*'},
    {'*', ' ',' ' , ' ', ' ', '*', ' ',' ', ' ', '*'},
    {'*', ' ',' ' , ' ', ' ', ' ', ' ',' ', ' ', '*'},
    {'*', ' ',' ' , ' ', ' ', ' ', ' ',' ', ' ', '*'},
    {'*', ' ',' ' , ' ', ' ', '*', ' ',' ', ' ', '*'},
    {'*', ' ',' ' , ' ', ' ', '*', ' ',' ', ' ', '*'},
    {'*', '*','*','*','*','*','*','*','*','*'}
  };

  printf("Before: \n");
  display_grid(grid, SIZE, SIZE);
  printf("\n\n");

  flood_fill(grid, 3, 3, '~');
  printf("After Flood Fill: \n");
  display_grid(grid, SIZE, SIZE);

  return 0;
}
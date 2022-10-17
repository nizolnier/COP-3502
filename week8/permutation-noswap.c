/*
Tanvir Ahmed
This code performs permuation of the numbers for 0 to n-1 for a given n.
This approach is different compared to the swapping approach we have learned to perform permuation of the characters in a string.
This approach uses a "used array" to track whether a number was already used in a particular iteration of the permuation process. Thr use of "used array", could be very useful as you can convert different types and objects permuation into 0 to n-1 permuation problem 
*/

#include <stdio.h>
#define SIZE 3

void printPermutArray(int arr[], int n)
{
  for(int i=0; i<n; i++)
    printf("%d ", arr[i]);
  printf("\n");
  
}

//the used array keep track which number is used and which number to be transferred to the perm

void mypermute(int arr[], int used[], int k, int n)
{
  if(k == n)
    printPermutArray(arr, n); //if k reaches the length print the result
  
  for(int i=0; i<n; i++)
  {
    if(!used[i]) //if i was not used
    {
      used[i] = 1; //mark that it is used
      arr[k] = i; //transfer i to the the perm array at kth position
      mypermute(arr, used, k+1, n); //increase k and grow further
      used[i] = 0; //unmark i for next process
    }
  }
  

}

int main(void) {
  int perm[SIZE] = {0}; //to build and store the permuation
  int used[SIZE] = {0}; //tracking which index/object is used
  mypermute(perm, used, 0, SIZE);

  printf("Hello World\n");
  return 0;
}
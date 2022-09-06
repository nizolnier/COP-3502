// Arup Guha
// 1/28/08
// Example for COP 3502

// Dynamic memory allocation for an array of strings.
// In this implementation, we dynamically allocate an array of arrays.
// First, we allocate a pointer for each word read in from the file.
// Then we allocate space the maximum amount of space for each string.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH     256

char** readList(char* fileName, int* wordsCount);
void printList(char** pList, int length);
void freeList(char** pList, int length);

int main() {

    char fileName[50];
    char** pList;
    int numWords;

    // Get the filename.
    printf("Enter the file name.\n");
    scanf("%s", fileName);

    // Read in the list storing it in pList.
    // numWords will store the number of words in the file.
    pList = readList(fileName, &numWords);

    // Print these words to check that our read worked and free the memory.
    printList(pList, numWords);
    freeList(pList, numWords);
    return 0;
}

// Pre-conditions: fileName is the name of a valid file with the proper
//                 format, and wordsCount is a pointer to an integer that will
//                 store the number of words read in.
// Post-condition: A pointer to an array of pointers storing all the words in
//                 filename will be returned.
char** readList(char* fileName, int* wordsCount) {

  char** pList = NULL;
  char word[MAX_STRING_LENGTH];
  int i, wordLength;

  FILE* pFile = fopen(fileName, "r");   // open file.

  if (pFile != NULL){
    /* read the 1st line, get to know how many words in the dictionary. */
    fscanf(pFile, "%d", wordsCount);

    /* Here we allocate space a pointer for each word in the list.
    Note that the space for the words themselves is NOT allocated here. */
    pList = malloc(*wordsCount * sizeof(char *));

    for (i = 0; i < *wordsCount; i++){

      // Allocate the maximum amount of space for this individual word.
      pList[i] = malloc((MAX_STRING_LENGTH+1)*sizeof(char));

      // read in this word.
      fscanf(pFile, "%s", pList[i]);
    }

    fclose(pFile);    // close file.
  }

  return pList;
}

// Pre-condition: pList is a pointer to an array of pointers, each of which
//                already stores a string. length is the number of strings
//                stored in the structure.
// Post-condition: All of the strings stored in pList will be printed.
void printList(char** pList, int length) {
     int i;

     // Just loop through each pointer and print the appropriate string.
     for (i=0; i<length; i++)
         printf("%s\n", pList[i]);
}

// Pre-condition: pList is a pointer to an array of pointers, each of which
//                already stores a string. length is the number of strings
//                stored in the structure.
// Post-condition: The memory for the structure pointed to by pList will be
//                 freed.
void freeList(char** pList, int length) {

     int i;

     // Free the memory for each individual word.
     for (i=0; i<length; i++)
         free(pList[i]);

     // Free the pointers to each word.
     free(pList);
}

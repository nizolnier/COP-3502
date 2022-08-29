#include <stdio.h>

typedef struct bookRec
{
    float price;
    char name[7];
} Book;

int main()
{
    // if you use typedef, you don’t have to write struct  every time when you declare a variable of your  structure
    Book temp; // this line is possible as we have used typedef
    Book *aPtr;

    aPtr = &temp;
    scanf("%d %s", &(aPtr->price), aPtr->name);

    scanf("%d %s", &temp.price, temp.name);
}

#include <stdio.h>

int main(void) {
    int a = -1;
    if(a != -1) {
        // check
    }

    // int *p1 = 20; - segmentation fault (accessing ilegal memory)

    int *p1;
    p1 = NULL;

    if(p1 != NULL) {
        *p1 = 20;
    }

    if(p1 == NULL) {
        p1 = &a;
    }

    if(p1) { // same as != NULL

    }

}

// pass by value - create a copy, needs return and type
// pass by reference - pass the location, receives it and deferrences it (changes content)
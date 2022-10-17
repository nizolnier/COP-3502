#include <stdio.h>

int f(int n) {
    if(n <= 5)
        return n;
    else
        return f(n-1) + f(n-2);
}

int main(void) {
    
    int ans = f(8);

    printf("%d", ans);
    return 0;
}
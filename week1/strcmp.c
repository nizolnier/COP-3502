#include <stdio.h>

int main()
{
    char str1[] = "abcd", str2[] = "abde", str3[] = "abCd",
         str4[] = "abcd";
    int result;
    result = strcmp(str1, str2);
    printf("strcmp(str1, str2) = %d\n", result);
    result = strcmp(str2, str1);
    printf("strcmp(str2, str1) = %d\n", result);
    result = strcmp(str1, str3);
    printf("strcmp(str1, str3) = %d\n", result);
    result = strcmp(str3, str1);
    printf("strcmp(str3, str1) = %d\n", result);
    result = strcmp(str1, str4);
    printf("strcmp(str1, str4) = %d\n", result);
    result = strcmp(str4, str1);
    printf("strcmp(str4, str1) = %d\n", result);
    return 0;
}

/*output
strcmp(str1, str2) = -1
strcmp(str2, str1) = 1
strcmp(str1, str3) = 32
strcmp(str3, str1) = -32
strcmp(str1, str4) = 0
strcmp(str4, str1) = 0
*/
// Pre-condition: string is a string of length n or greater.
// Post-condition: Prints out the first n characters of string in reverse order.
void print_reverse(char string[], int n)
{

    // Only one character to print, so print it!
    if (n == 1)
        printf("%c", string[0]);

    // Solve the problem recursively: print the last character, then reverse
    // the substring without that last character.
    else
    {
        printf("%c", string[n - 1]);
        print_reverse(string, n - 1);
    }
}

void printReverse(char word[], int length)
{
    if (length > 0)
    {
        printf("%c", word[length - 1]);
        printReverse(word, length - 1);
    }
}
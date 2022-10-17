int powerB(int base, int exp)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    if (exp % 2 == 0) // if exp is even
        return powerB(base * base, exp / 2);
    else // if exp is odd
        return powerB(base * base, exp / 2) * base;
}
int main()
{
    printf("%d", powerB(2, 5));
    return 0;
}
// Pre-conditions: e is greater than or equal to 0.
// Post-conditions: returns b^e
int power(int base, int exponent)
{
    if (exponent == 0)
        return 1;
    else
        return (base * Power(base, exponent - 1));
}
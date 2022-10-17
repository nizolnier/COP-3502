#define TIP_RATE 0.15
// Pre-condition: Both parameters are integers with the first one being less than or equal to the second one
// Post-condition: A tip chart will be printed out, with a row for each dollar amount ranging in between the value of the two parameters.void
Tip_Chart(int first_val, int last_val)
{
    if (!(first_val > last_val))
    {
        printf("On a meal of $%d", first_val);
        printf(" you should tip $%lf\n", first_val * TIP_RATE);
        Tip_Chart(first_val + 1, last_val);
    }
}

int main()
{
    Tip_Chart(1, 10);
}

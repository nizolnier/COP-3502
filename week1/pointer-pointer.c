int main()
{
    int i = 3, *j, **k;
    j = &i;
    k = &j;                             // K has the capability to hold address of pointer
    printf("\nAddress of i = %u", &i);  // print address of i
    printf("\nAddress of i = %u", j);   // print address of i
    printf("\nAddress of i = %u", *k);  // print address of i
    printf("\nAddress of j = %u", &j);  // print address of j
    printf("\nAddress of j = %u", k);   // print address of j
    printf("\nAddress of k = %u", &k);  // print address of k
    printf("\nValue of j = %u", j);     // print value of j, which is address of i
    printf("\nValue of k = %u", k);     // print value of k, which is address of j
    printf("\nValue of i = %d", i);     // print 3
    printf("\nValue of i = %d", *(&i)); // print 3
    printf("\nValue of i = %d", *j);    // print print 3
    printf("\nValue of i = %d", **k);   // print 3. As *k = j, and *j = i, i=3
    return 0;
}

int multiply(int m, int n) {
    if(m == 0 || n == 0)
        return 0;
    
    return (m + multiply(m, n-1));
}
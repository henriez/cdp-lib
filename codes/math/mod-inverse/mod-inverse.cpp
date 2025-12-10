int modInverse(int a, int m) {
    int x, y;
    int g = extendedGcd(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}
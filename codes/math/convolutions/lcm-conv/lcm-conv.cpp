vector<mint<MOD>> lcm_conv(vi a, vi b){
    int n = (int)max(a.size(), b.size());
    a.resize(n);
    b.resize(n);
    vector<mint<MOD>> c(n), x(n), y(n);
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j += i) {
            x[j] += a[i];
            y[j] += b[i];
        }
        c[i] = x[i]*y[i];
    }
    for (int i = 1; i < n; i++)
        for (int j = 2 * i; j < n; j += i) 
            c[j] -= c[i];

    return c;
}
void fwht(vector<mint<MOD>> &a, bool inv){
    int n = a.size(); // must be pow of 2
    for (int step = 1; step < n; step <<= 1){
        for (int i = 0; i < n; i += 2*step) {
            for (int j = i; j < i+step; j++){
                auto u = a[j];
                auto v = a[j+step];
                a[j] = u+v;
                a[j+step] = u-v;
            }
        }
    }
    if (inv) for (auto &x : a) x /= n;
}

vector<mint<MOD>> xor_conv(vector<mint<MOD>> a, vector<mint<MOD>> b){
    int n = a.size();
    fwht(a,0), fwht(b, 0);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    fwht(a,1);
    return a;
}
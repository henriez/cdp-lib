vector<mint> gcd_conv(vi a, vi b){
  int n = (int)max(a.size(), b.size());
  a.resize(n); b.resize(n);
  vector<mint> c(n);
  for (int i = 1; i < n; i++) {
    mint x = 0;
    mint y = 0;
    for (int j = i; j < n; j += i) {
      x += a[j];
      y += b[j];
    }
    c[i] = x*y;
  }
  for (int i = n-1; i >= 1; i--)
    for (int j = 2*i; j < n; j += i) 
      c[i] -= c[j];
  return c;
}
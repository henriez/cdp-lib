vector<mint> or_conv(vector<mint> a, vector<mint> b){
  int n = a.size(); // must be pow of 2
  for (int j = 1; j < n; j <<= 1) {
    for (int i = 0; i < n; i++) {
      if (i&j) {
        a[i] += a[i^j];
        b[i] += b[i^j];
      }
    }
  }
  for (int i = 0; i < n; i++) a[i] *= b[i];
  for (int j = 1; j < n; j <<= 1)
	for (int i = 0; i < n; i++)
	  if (i&j) a[i] -= a[i^j];
  return a;
}
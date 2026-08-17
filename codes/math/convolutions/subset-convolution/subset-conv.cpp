vector<mint> subset_conv(const vector<mint>& a, const vector<mint>& b) {
  int n = a.size(); // must be pow of 2
  int k = __builtin_ctz(n);

  vector<vector<mint>> fa(k+1, vector<mint>(n, 0));
  vector<vector<mint>> fb(k+1, vector<mint>(n, 0));
  vector<vector<mint>> fc(k+1, vector<mint>(n, 0));

  for (int i = 0; i < n; i++) {
    int pc = __builtin_popcount(i);
    fa[pc][i] = a[i];
    fb[pc][i] = b[i];
  }

  for (int pc = 0; pc <= k; pc++) {
    for (int j = 1; j < n; j <<= 1) {
      for (int i = 0; i < n; i++) {
        if (i & j) {
          fa[pc][i] += fa[pc][i ^ j];
          fb[pc][i] += fb[pc][i ^ j];
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int pc = 0; pc <= k; pc++) {
      for (int j = 0; j <= pc; j++) {
        fc[pc][i] += fa[j][i] * fb[pc - j][i];
      }
    }
  }

  for (int pc = 0; pc <= k; pc++) {
    for (int j = 1; j < n; j <<= 1) {
      for (int i = 0; i < n; i++) {
        if (i & j) {
          fc[pc][i] -= fc[pc][i ^ j];
        }
      }
    }
  }

  // 5. Gather results
  vector<mint> c(n);
  for (int i = 0; i < n; i++) {
    c[i] = fc[__builtin_popcount(i)][i];
  }
  
  return c;
}
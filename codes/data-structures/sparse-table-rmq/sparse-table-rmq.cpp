
struct SparseTable {
  vector<vector<ii>> st;

  void build(const vi &a) {
    int n = a.size();
    int max_log = __bit_width(n); 
    st.assign(max_log, vector<ii>(n));
    for (int i = 0; i < n; i++) {
      st[0][i] = {a[i], i};
    }
    for (int i = 1; i < max_log; i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        // Combine the two halves
        st[i][j] = std::min(st[i-1][j], st[i-1][j + (1 << (i-1))]);
      }
    }
  }

  // Returns min value and index in range [l, r] inclusive
  ii min(int l, int r) {
    int len = r - l + 1;
    int k = __bit_width(len) - 1;
    return std::min(st[k][l], st[k][r - (1<<k) + 1]);
  }
};
// [l,r] interval cnvention and 0-based indexing
struct BIT2D {
  vector<ll> bit;
  int n, m;
  BIT2D(int _n, int _m){
    n = _n; m = _m;
    bit.resize((n+1)*(m+1));
  }
  BIT2D(vector<vector<ll>> &a) {
    n = a.size();
    m = a[0].size();
    bit.resize((n+1)*(m+1));

    for (int i = 1; i <= n; i++) 
      for (int j = 1; j <= m; j++) 
        bit[i*(m+1) + j] = a[i-1][j-1];

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int nxt = j + (j&-j);
        if (nxt<=m) bit[i*(m+1)+nxt] += bit[i*(m+1)+j];
      }
    }
    for (int i = 1; i <= n; i++) {
      int nxt = i + (i&-i);
      if (nxt <= n) {
        for (int j = 1; j <= m; j++) 
          bit[nxt*(m+1) + j] += bit[i*(m+1) + j];
      }
    }
  }
  void add(int si, int sj, ll v){
    for(int i = si+1; i <= n; i+=i&-i)
      for (int j = sj+1; j <= m; j+=j&-j)
        bit[i*(m+1) + j] += v;
  }
  ll presum(int si, int sj){
    ll ans = 0;
    for (int i = si+1; i > 0; i-=i&-i)
      for (int j = sj+1; j > 0; j-=j&-j)
        ans += bit[i*(m+1) + j];
    return ans;
  }
  ll sum(ii ab, ii cd){
    auto [a,b] = ab;
    auto [c,d] = cd;
    return presum(c,d) - presum(a-1,d) - presum(c,b-1) + presum(a-1,b-1);
  }
};
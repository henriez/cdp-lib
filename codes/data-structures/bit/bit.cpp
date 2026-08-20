// [l,r] interval convention and 0-indexed parameters
struct BIT {
  vector<ll> bit;
  int n;
  BIT(int _n = 0){
    n = _n;
    bit.assign(n+1,0ll);
  }
  ll presum(int i){
    ll ans = 0;
    for (++i; i > 0; i -= i&-i) 
      ans += bit[i];
    return ans;
  }
  ll sum(int l, int r){
    return presum(r) - presum(l-1);
  }
  void add(int i, ll v){
    for (++i; i <= n; i += i&-i) 
      bit[i] += v;
  }
  int find_kth(int k) {
    int pos = 0, sum = 0, step = 1;
    while (step <= n) step <<= 1;
    step >>= 1;
    for (; step >= 1; step >>= 1) {
      if (pos+step <= n && sum + bit[pos+step] <= k) {
        pos += step;
        sum += bit[pos];
      }
    }
    return pos;
  }
};
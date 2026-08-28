#define D 60 // max bits
struct XorBasis {
  ll a[D] = {0};
  int sz = 0;
  // Returns {represented_part, orthogonal_part}
  pair<ll, ll> reduce(ll x) {
    ll orig = x;
    for (int i = D-1; i >= 0; i--)
      if ((x>>i&1) && a[i]) x ^= a[i];
    return {orig^x, x};
  }
  bool insert(ll x) {
    for (int i = D-1; i >= 0; i--) {
      if (!(x>>i&1)) continue;
      if (!a[i]) {
        a[i] = x; sz++;
        return true;
      }
      x ^= a[i];
    }
    return false;
  }
  bool check(ll x) { return reduce(x).second == 0; }
  ll max_xor(ll val = 0) {
    for (int i = D-1; i >= 0; i--)
      val = max(val, val^a[i]);
    return val;
  }
  ll span_size() { return 1ll << sz; }
};
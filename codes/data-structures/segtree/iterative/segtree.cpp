// ITERATIVE - implemented for sum + point assignment
struct segtree {
  struct node {
    int sum = 0; // data
    static node combine(const node& a, const node& b) {
      return {a.sum + b.sum};
    }
    void apply(int v) {
      sum = v; 
    }
  };
  int n;
  vector<node> t;
  void init(const vi& a) {
    n = a.size();
    t.assign(2*n, node());
    for (int i = 0; i < n; i++) t[n + i].apply(a[i]);
    for (int i = n-1; i > 0; i--) t[i] = node::combine(t[i<<1], t[i<<1|1]);
  }
  void set(int p, int v) {
    for (t[p += n].apply(v), p >>= 1; p > 0; p >>= 1) {
      t[p] = node::combine(t[p<<1], t[p<<1|1]);
    }
  }
  node query(int l, int r) {
    node resL, resR;
    for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
      if (l&1) resL = node::combine(resL, t[l++]);
      if (r&1) resR = node::combine(t[--r], resR);
    }
    return node::combine(resL, resR);
  }
};
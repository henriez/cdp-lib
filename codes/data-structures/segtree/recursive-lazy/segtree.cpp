// LAZY recursive - implemented for sum + range AP addition
struct segtree {
  struct node {
    struct tag {
      int a = 0, d = 0;
      bool has = false;
    };
    int sum = 0; // data
    tag lazy;
    static node combine(const node& left, const node& right) {
      return {left.sum + right.sum, {0, 0, false}};
    }
    void leaf(int v) { sum = v; }
    void apply(tag t, int lx, int rx) {
      if (!t.has) return;
      int len = rx - lx;
      
      // Sum of (t.a + t.d * i) for i in [lx, rx-1]
      sum += t.a * len + t.d*len*(lx+rx-1)/2; 
      
      lazy.a += t.a;
      lazy.d += t.d;
      lazy.has = true;
    }
    void push(node& left, node& right, int lx, int rx) {
      if (lazy.has) {
        int mx = (lx + rx) / 2;
        left.apply(lazy, lx, mx);
        right.apply(lazy, mx, rx);
        lazy = {0, 0, false};
      }
    }
  };

  int size;
  vector<node> t;

  void init(int n) {
    size = 1;
    while (size < n) size *= 2;
    t.assign(2*size, node());
    build(0, 0, size, n);
  }
  void build(int x, int lx, int rx, int n) {
    if (rx-lx == 1) {
      if (lx < n) t[x].leaf(0);
      return;
    }
    int mx = (lx + rx) / 2;
    build(2*x+1, lx, mx, n);
    build(2*x+2, mx, rx, n);
    t[x] = node::combine(t[2*x+1], t[2*x+2]);
  }
  void push(int x, int lx, int rx) {
    t[x].push(t[2*x+1], t[2*x+2], lx, rx);
  }
  void rangeUpdate(int l, int r, node::tag v, int x, int lx, int rx) {
    if (lx >= r || rx <= l) return;
    if (lx >= l && rx <= r) {
      t[x].apply(v, lx, rx);
      return;
    } 
    push(x, lx, rx);
    int mx = (lx + rx) / 2;
    rangeUpdate(l, r, v, 2*x+1, lx, mx);
    rangeUpdate(l, r, v, 2*x+2, mx, rx);
    t[x] = node::combine(t[2*x+1], t[2*x+2]);
  }
  void rangeUpdate(int l, int r, int a, int d) {
    rangeUpdate(l, r, {a - l*d, d, true}, 0, 0, size);
  }
  node query(int l, int r, int x, int lx, int rx) {
    if (lx >= r || rx <= l) return node();
    if (lx >= l && rx <= r) return t[x]; 
    push(x, lx, rx);
    int mx = (lx+rx) / 2;
    return node::combine(
      query(l, r, 2*x+1, lx, mx), 
      query(l, r, 2*x+2, mx, rx)
    );
  }
  node query(int l, int r) {
    return query(l, r, 0, 0, size);
  }
};

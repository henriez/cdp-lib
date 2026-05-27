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

// LAZY ITERATIVE - implemented for sum + range addition
// TODO: test
struct segtree {
  struct node {
    struct tag {
      int add = 0;
      bool has = false;
    };
    int sum = 0; // data
    int len = 0;
    tag lazy;

    static node combine(const node& a, const node& b) {
      if (a.len == 0) return b;
      if (b.len == 0) return a;
      return {a.sum + b.sum, a.len + b.len, {0, false}};
    }
    void apply(tag t) {
      if (!t.has) return;
      sum += len * t.add;
      lazy.add += t.add;
      lazy.has = true;
    }
    void push(node& left, node& right) {
      if (lazy.has) {
        left.apply(lazy);
        right.apply(lazy);
        lazy = {0, false};
      }
    }
    void pull(const node& left, const node& right) {
      tag cur = lazy; 
      *this = combine(left, right); 
      apply(cur); 
    }
  };
  int n, h;
  vector<node> t;
  void init(const vi& a) {
    int sz = a.size();
    n = 1; h = 0;
    while (n < sz) { n*=2; h++; } 
    
    t.assign(2*n, node());
    
    for (int i = 0; i < n; i++) t[i+n].len = 1;
    for (int i = 0; i < sz; i++) t[i+n].apply({a[i], true});
    for (int i = n-1; i > 0; i--) t[i].pull(t[i<<1], t[i<<1|1]);
  }
  void build(int p) {
    while (p > 1) p >>= 1, t[p].pull(t[p<<1], t[p<<1|1]);
  }
  void push(int p) {
    for (int s = h; s > 0; s--) {
      int i = p >> s;
      t[i].push(t[i<<1], t[i<<1|1]);
    }
  }
  void rangeUpdate(int l, int r, node::tag v) {
    if (l==r) return;
    l += n, r += n;
    int l0 = l, r0 = r;
    
    push(l0); push(r0-1);
    for (; l < r; l >>= 1, r >>= 1) {
      if (l&1) t[l++].apply(v);
      if (r&1) t[--r].apply(v);
    }
    build(l0); build(r0-1);
  }
  node query(int l, int r) {
    if (l == r) return node();
    l += n, r += n;
    push(l); push(r-1);
    node resL = node(), resR = node();
    for (; l < r; l >>= 1, r >>= 1) {
      if (l&1) resL = node::combine(resL, t[l++]);
      if (r&1) resR = node::combine(t[--r], resR);
    }
    return node::combine(resL, resR);
  }
};

// LAZY recursive - implemented for sum + range AP addition
// TODO: test
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

    void apply(tag t, int len) {
      if (!t.has) return;
      sum += len * (2 * t.a + (len - 1) * t.d) / 2;
      lazy.a += t.a;
      lazy.d += t.d;
      lazy.has = true;
    }

    void push(node& left, node& right, int llen, int rlen) {
      if (lazy.has) {
        left.apply(lazy, llen);
        tag right_tag = {lazy.a + llen * lazy.d, lazy.d, true};
        right.apply(right_tag, rlen);
        lazy = {0, 0, false};
      }
    }
  };
  int size;
  vector<node> t;
  void init(const vi& a) {
    size = 1;
    while (size < a.size()) size *= 2;
    t.assign(2*size, node());
    build(0,0,size,a);
  }
  void build(int x, int lx, int rx, const vi& a) {
    if (rx-lx == 1) {
      if (lx < a.size()) t[x].leaf(a[lx]);
      return;
    }
    int mx = (lx+rx)/2;
    build(2*x+1,lx,mx,a);
    build(2*x+2,mx,rx,a);
    t[x] = node::combine(t[2*x+1], t[2*x+2]);
  }
  void push(int x, int lx, int rx) {
    int mx = (lx + rx) / 2;
    t[x].push(t[2*x+1], t[2*x+2], mx-lx, rx-mx);
  }
  void rangeUpdate(int l, int r, node::tag v, int x, int lx, int rx) {
    if (lx >= r || rx <= l) return;
    if (lx >= l && rx <= r) {
      t[x].apply(v, rx-lx);
      return;
    }
    push(x, lx, rx);
    int mx = (lx+rx)/2;
    rangeUpdate(l, r, v, 2*x+1, lx, mx);
    rangeUpdate(l, r, v, 2*x+2, mx, rx);
    t[x] = node::combine(t[2*x+1], t[2*x+2]);
  }
  void rangeUpdate(int l, int r, node::tag v) {
    rangeUpdate(l,r,v,0,0,size);
  }
  node query(int l, int r, int x, int lx, int rx) {
    if (lx >= r || rx <= l) return node();
    if (lx >= l && rx <= r) return t[x];
    push(x, lx, rx);
    int mx = (lx+rx)/2;
    return node::combine(
      query(l, r, 2*x+1, lx, mx), 
      query(l, r, 2*x+2, mx, rx)
    );
  }
  node query(int l, int r) {
    return query(l, r, 0, 0, size);
  }
};
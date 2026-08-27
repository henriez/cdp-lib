// PERSISTENT - implemented for sum + point assignment
struct persistent_segtree {
  struct node {
    int sum = 0;
    int lc = 0, rc = 0; // indices to left and right children
    static node combine(const node& left, const node& right) {
        return {left.sum+right.sum};
    }
    void leaf(int v) { sum = v; }
  };
  int size;
  vector<node> t;
  vi root; // root node id for each version
  persistent_segtree(const vi &a) {
    size = 1;
    while (size < a.size()) size <<= 1;
    t.push_back(node());
    root.push_back(build(0, size, a));
  }
  int build(int lx, int rx, const vi &a) {
    int x = t.size();
    t.push_back(node());
    if (rx-lx == 1) {
      if (lx < a.size()) t[x].leaf(a[lx]);
      return x;
    }
    int mx = (lx+rx)/2;
    t[x].lc = build(lx, mx, a);
    t[x].rc = build(mx, rx, a);
    // do not override pointers lc,rc
    t[x].sum = node::combine(t[t[x].lc], t[t[x].rc]).sum;
    return x;
  }
  int update(int i, int v, int old, int lx, int rx) {
    int x = t.size();
    t.push_back(t[old]);
    if (rx-lx == 1) {
      t[x].leaf(v);
      return x;
    }
    int mx = (lx+rx)/2;
    if (i < mx) t[x].lc = update(i, v, t[old].lc, lx, mx);
    else t[x].rc = update(i, v, t[old].rc, mx, rx);
    // do not override pointers lc,rc
    t[x].sum = node::combine(t[t[x].lc], t[t[x].rc]).sum;
    return x;
  }
  int update(int version, int i, int v) {
    // assign to root[version] if this update 
    // should not trigger another version
    int x = update(i,v,root[version],0,size);
    root.push_back(x);
    return root.size()-1;
  }
  int copy_version(int version) {
    root.push_back(root[version]);
    return root.size() - 1;
  }
  node query(int l, int r, int x, int lx, int rx) {
    if (lx >= r || rx <= l || x == 0) return node();
    if (lx >= l && rx <= r) return t[x]; 
    int mx = (lx+rx)/2;
    return node::combine(
      query(l, r, t[x].lc, lx, mx), 
      query(l, r, t[x].rc, mx, rx)
    );
  }
  node query(int version, int l, int r) {
    return query(l, r, root[version], 0, size);
  }
};

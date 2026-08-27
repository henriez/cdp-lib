struct HLD {
  int n, timer = 0;
  vvi adj;
  vi par, dep, sz, heavy, head, val, tin, tout; 
  segtree seg;
  void init(int _n, vi& _val, vvi& _adj) {
    n = _n;
    adj = _adj;
    val = _val;
    par = heavy = vi(n,-1);
    dep = sz = head = tin = tout = vi(n);
    timer = 0;
    dfs1(0); dfs2(0,0);
    vi linear(n);
    for (int u = 0; u < n; u++)
      linear[tin[u]] = val[u];
    seg.init(linear);
  }
  int dfs1(int u) {
    sz[u] = 1;
    int max_sz = 0;
    for (int v : adj[u]) {
      if (v == par[u]) continue;
      par[v] = u;
      dep[v] = dep[u] + 1;
      int size = dfs1(v);
      sz[u] += size;
      if (size > max_sz) {
        max_sz = size;
        heavy[u] = v;
      }
    }
    return sz[u];
  }
  void dfs2(int u, int h) {
    tin[u] = timer++;
    head[u] = h;
    if (heavy[u] != -1)
      dfs2(heavy[u], h);
    for (int v : adj[u]) {
      if (v != par[u] && v != heavy[u])
        dfs2(v, v);
    }
    tout[u] = timer;
  }
  void update(int u, int val) {
    seg.set(tin[u], val);
  }
  void rangeUpdate(int u, int v, int x) {
    while (head[u] != head[v]) {
      if (dep[head[u]] < dep[head[v]]) swap(u, v);
      seg.rangeUpdate(tin[head[u]], tin[u] + 1, x);
      u = par[head[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    seg.rangeUpdate(tin[u], tin[v] + 1, x);
  }
  void update_subtree(int u, int x) {
    seg.rangeUpdate(tin[u], tout[u], x);
  }
  segtree::node query(int u, int v) {
    segtree::node ans;
    while (head[u] != head[v]) {
      if (dep[head[u]] < dep[head[v]])
        swap(u, v);
      ans = seg.merge(ans, seg.query(tin[head[u]], tin[u]+1));
      u = par[head[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    ans = seg.merge(ans, seg.query(tin[u], tin[v]+1));
    return ans;
  }
  segtree::node query_subtree(int u){
    return seg.query(tin[u], tout[u]);
  }
};
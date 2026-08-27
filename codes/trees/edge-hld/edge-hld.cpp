struct EdgeHLD {
  int n, timer = 0;
  vvii adj;
  vi par, dep, sz, heavy, head, val, tin, tout;
  segtree seg;
  void init(int _n, vvii& _adj) {
    n = _n;
    adj = _adj;
    par = heavy = vi(n,-1);
    val = dep = sz = head = tin = tout = vi(n);
    timer = 0;
    // edgeWeight[v] = weight of edge (par[v], v), for v>0
    // root (0) has no par, so its val is (0)
    dfs1(0,0,0);
    dfs2(0, 0);
    vi linear(n);
    for (int u = 0; u < n; u++)
      linear[tin[u]] = val[u]; // position stores edge weight
    seg.init(linear);
  }
  int dfs1(int u, int p, int w) {
    sz[u] = 1;
    par[u] = p;
    val[u] = w;
    int max_sz = 0;
    for (auto[v,w] : adj[u]) {
      if (v == p) continue;
      dep[v] = dep[u] + 1;
      int size = dfs1(v, u, w);
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
    for (auto [v,w] : adj[u]) {
      if (v != par[u] && v != heavy[u])
        dfs2(v, v);
    }
    tout[u] = timer;
  }
  // u must be the child of the edge
  void update_edge(int u, int val) {
    seg.set(tin[u], val);
  }
  void rangeUpdate(int u, int v, int x) {
    while (head[u] != head[v]) {
      if (dep[head[u]] < dep[head[v]]) swap(u, v);
      seg.rangeUpdate(tin[head[u]], tin[u] + 1, x);
      u = par[head[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    seg.rangeUpdate(tin[u]+1, tin[v]+1, x);
  }
  void update_subtree(int u, int x) {
    // updates all in subtree of u (edge p[u] -> u)
    seg.rangeUpdate(tin[u] + 1, tout[u], x);
  }
  segtree::node query(int u, int v) {
    segtree::node ans;
    while (head[u] != head[v]) {
      if (dep[head[u]] < dep[head[v]]) swap(u, v);
      ans = seg.merge(ans, seg.query(tin[head[u]], tin[u]+1));
      u = par[head[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    ans = seg.merge(ans, seg.query(tin[u]+1, tin[v]+1));
    return ans;
  }
  segtree::node query_subtree(int u) {
    // query all edges in subtree of u
    return seg.query(tin[u] + 1, tout[u]);
  }
};
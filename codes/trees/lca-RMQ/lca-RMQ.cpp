struct LCARMQ {
  SparseTable st;
  vi tin, dep, et_nodes, et_deps;

  LCARMQ(vvi &adj){
    int n = adj.size(), timer = 0;
    tin = dep = vi(n);
    et_nodes.reserve(2*n);
    et_deps.reserve(2*n);

    auto dfs = [&](auto &&dfs, int u, int p) -> void {
      et_nodes.push_back(u);
      et_deps.push_back(dep[u]);
      tin[u] = timer++;
      for (int v : adj[u]) if (v != p) {
        dep[v] = dep[u]+1;
        dfs(dfs,v,u);
        et_nodes.push_back(u);
        et_deps.push_back(dep[u]);
      }
      timer++;
    };
    dfs(dfs,0,0);

    st.build(et_deps);
  }

  int get(int u, int v){
    int tu = tin[u], tv = tin[v];
    if (tu > tv) swap(tu,tv);
    auto [val,id] = st.min(tu,tv);
    return et_nodes[id];
  }
};
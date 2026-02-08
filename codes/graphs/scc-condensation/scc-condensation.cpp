struct SCCCondenser {
  int n, timer, scc_cnt;
  vi in, low, scc;
  stack<int> st;

  SCCCondenser(const vvi& adj) {
    n = adj.size();
    in.assign(n, 0);
    low.assign(n, 0);
    scc.assign(n, -1);
    timer = scc_cnt = 0;
    for (int i = 0; i < n; ++i)
      if (!in[i]) dfs(i, adj);
  }

  void dfs(int u, const vvi& adj) {
    in[u] = low[u] = ++timer;
    st.push(u);
    for (int v : adj[u]) {
      if (!in[v]) {
        dfs(v, adj);
        low[u] = min(low[u], low[v]);
      } else if (scc[v] == -1) { 
        low[u] = min(low[u], in[v]);
      }
    }
    if (low[u] == in[u]) {
      while (true) {
        int v = st.top(); st.pop();
        scc[v] = scc_cnt;
        if (u == v) break;
      }
      scc_cnt++;
    }
  }

  // Returns {DAG, Aggregated Values}
  pair<vvi, vi> build(const vvi& adj, const vi& val) {
    vvi dag(scc_cnt);
    vi scc_val(scc_cnt);
    set<ii> edges;

    for (int u = 0; u < n; ++u) {
      scc_val[scc[u]] += val[u]; // Aggregate values
      for (int v : adj[u]) {
        if (scc[u] != scc[v]) {
          if (edges.count({scc[u], scc[v]})) continue;
          edges.insert({scc[u], scc[v]});
          dag[scc[u]].push_back(scc[v]);
        }
      }
    }
    return {dag, scc_val};
  }
};
vvi build_bct(const vvi &adj){
  int n = adj.size();
  vi in(n,-1), low(n), st;
  int timer = 0;
  vvi bccs;

  auto dfs = [&](auto &&dfs, int u, int p) -> void {
    in [u] = low[u] = ++timer;
    st.push_back(u);
    if (p == -1 && adj[u].empty()){
      bccs.push_back({u});
      st.pop_back();
      return;
    }
    for (int v : adj[u]) if (v != p) {
      if (in[v] != -1) {
        low[u] = min(low[u], in[v]);
      } else {
        dfs(dfs,v,u);
        low[u] = min(low[u],low[v]);
        if (low[v] >= in[u]){
          bccs.push_back({u});
          while(1){
            int w = st.back();
            st.pop_back();
            bccs.back().push_back(w);
            if (w == v) break;
          }
        }
      }
    }
  };
  for (int i = 0; i < n; i++){
    if (in[i] == -1) dfs(dfs,i,-1);
  }
  vvi bct(n+bccs.size());
  for (int i = 0; i < bccs.size(); i++){
    int b = n+i;
    for (int u : bccs[i]){
      bct[u].push_back(b);
      bct[b].push_back(u);
    }
  }
  return bct;
}

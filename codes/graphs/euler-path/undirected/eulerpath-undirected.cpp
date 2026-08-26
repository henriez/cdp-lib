auto get_path = [&](int s = -1, int t = -1) -> vi {
  if (m == 0) return {};
  if (s != -1 && t != -1) {
    if (s != t && (deg[s]%2 == 0 || deg[t]%2 == 0)) 
        return {};
    if (s == t && deg[s]%2) return {};
  } 
  int odd = 0;
  for (int u = 0; u < n; u++) {
    if (deg[u]&1) {
      odd++;
      if (s == -1) s = u;
      else if (t == -1 && s != u) t = u;
    }
  }
  if (odd != 0 && odd != 2) return {};
  if (s == -1) {
    for (int u = 0; u < n; u++) {
      if (deg[u] > 0) {
        s = u; break;
      }
    }
  }
  if (odd == 2 && deg[s]%2 == 0) return {};
  if (odd == 2 && deg[t]%2 == 0) return {};
  vi path;
  vector<bool> used(m, false);
  auto dfs = [&](auto& dfs, int u) -> void {
    while (!adj[u].empty()) {
      auto [v, id] = adj[u].back();
      adj[u].pop_back();
      if (used[id]) continue;
      used[id] = true;
      dfs(dfs, v);
    }
    path.push_back(u);
  }; dfs(dfs, s);
  if (path.size() != m+1) return {}; 
  reverse(all(path));
  return path;
};
vi path = get_path(0,0);
if (path.empty()) {
  cout << "IMPOSSIBLE\n"; return;
}

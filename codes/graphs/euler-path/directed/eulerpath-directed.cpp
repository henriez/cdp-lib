auto get_path = [&](int s = -1, int t = -1) -> vi {
  if (m == 0) return {};
  if (s!=-1 && t!=-1){
    if (out[s]-in[s] != 1 || out[t]-in[t] != -1) return {};
  } 
  int cnt1 = 0, cnt2 = 0;
  for (int u = 0; u < n; u++) {
    int d = out[u]-in[u];
    if (d == 1) {
      if (s == -1) s = u;
      cnt1++;
    } else if (d == -1) {
      cnt2++;
      if (t == -1) t = u;
    } else if (in[u] != out[u]) return {};
  }

  if (!((cnt1==0 && cnt2==0) || (cnt1==1 && cnt2==1))) 
    return {};
  if (s == -1) {
    for (int i = 0; i < n; i++) {
      if (out[i] > 0) {
        s = i; break;
      }
    }
  }
  vi path;
  auto dfs = [&](auto& dfs, int u) -> void {
    while (!adj[u].empty()) {
      int v = adj[u].back();
      adj[u].pop_back();
      dfs(dfs, v);
    }
    path.push_back(u);
  }; dfs(dfs,s);
  if (path.size() != m+1) return {}; 
  reverse(all(path));
  return path;
};
vi path = get_path(0,n-1);
if (path.empty()) {
  cout << "IMPOSSIBLE\n"; return;
} 
for (int u : path) cout << u+1 << ' '; cout << '\n';
int matchings;
vi p, vis;
vii match;

int dfs(int u){
  if(vis[u]) return 0;
  vis[u] = 1;
  for(auto v: adj[u]){
    if(p[v] == -1 || dfs(p[v])){
      p[v] = u;
      return 1;
    }
  }
  return 0;
}

void kuhn(){
  matchings = 0;
  p = vi(n+m, -1);
  for(int i = 0; i < n; i++){
    vis = vi(n, 0);
    matchings += dfs(i);
  }
  for(int i = n; i < n+m; i++){
    if(p[i] != -1) match.push_back(ii(p[i], i));
  }
}

void create(){
  adj = vvi(n+m);
  for(int i = 0; i < k; i++){
    int u, v;
    cin >> u >> v; u--; v--;
    adj[u].push_back(v+n);
  }
}
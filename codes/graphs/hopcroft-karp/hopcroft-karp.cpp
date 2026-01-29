int n, m, k;
vvi adj;
vi p, dist; /*p is in matching for [0, n[ and parent for [n, n+m[*/

int bfs(){
  queue<int> q;
  dist = vi(n+m, inf);
  for(int i = 0; i < n; i++){
    if(p[i] == -1) q.push(i), dist[i] = 0;
  }
  int min_dist_match = inf;
  while(!q.empty()){
    int u = q.front(); q.pop();
    if(dist[u] > min_dist_match) continue;
    for(auto v: adj[u]){
      if(p[v] == -1) min_dist_match = dist[u];
      else if(dist[p[v]] == inf){
        dist[p[v]] = dist[u] + 1;
        q.push(p[v]);
      }
    }
  }
  return min_dist_match != inf;
}

int dfs(int u){
  for(auto v: adj[u]){
    if(p[v] == -1 || (dist[u]+1 == dist[p[v]] && dfs(p[v]))){
      p[v] = u;
      p[u] = 1;
      return true;
    }
  }
  dist[u] = inf;
  return false;
}

int hopkarp(){
  p = vi(n+m, -1);
  int matchings = 0;
  while(bfs()){
    for(int i = 0; i < n; i++){
      if(p[i] == -1 && dfs(i)) matchings++;
    }
  }
  return matchings;
}

void create(){
  adj = vvi(n+m);
  for(int i = 0; i < k; i++){
    int u, v;
    cin >> u >> v; u--; v--;
    v += n;
    adj[u].push_back(v);
  }
}
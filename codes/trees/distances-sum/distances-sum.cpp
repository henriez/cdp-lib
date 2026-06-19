vvi adj;
vi sum_going_down, sum_going_up, sz;

void dfs(int u, int p){
  for (auto v : adj[u]){
    if (v == p) continue;
    dfs(v,u);
    sz[u] += sz[v];
    sum_going_down[u] += sum_going_down[v];
  }
  sum_going_down[u] += sz[u];
}

void dfs2(int u, int p, int par_ans){
  int up_amount = sz[0] - sz[u];
  sum_going_up[u] += par_ans + up_amount;
  int sum = sum_going_down[u];
  for (auto v : adj[u]){
    if (v == p) continue;
    int par_amount = sz[0] - sz[v];
    // new p_ans is going up for is going up for p
    // + go up to u and go down to other subtrees 
    dfs2(v,u, par_ans + par_amount + sum - (sum_going_down[v]+sz[v]));
  }
}

void solve(){
  adj = vvi(n);
  sum_going_down = sum_going_up = vi(n);
  sz = vi(n,1);
  // read adj
  dfs(0,0);
  dfs2(0,0,0);

  for (int i = 0; i < n; i++){
    cout << sum_going_down[i]+sum_going_up[i] << ' ';
  }
  cout << endl;
}
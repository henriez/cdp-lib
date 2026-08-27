vvi adj;
vi sum_down, sum_up, sz;
void dfs(int u, int p){
  for (auto v : adj[u]){
    if (v == p) continue;
    dfs(v,u);
    sz[u] += sz[v];
    sum_down[u] += sum_down[v];
  }
  sum_down[u] += sz[u];
}
void dfs2(int u, int p, int par_ans){
  int up_amount = sz[0] - sz[u];
  sum_up[u] += par_ans + up_amount;
  int sum = sum_down[u];
  for (auto v : adj[u]){
    if (v == p) continue;
    // new p_ans is going up for is going up for p
    // + go up to u and go down to other subtrees 
    dfs2(v,u, par_ans + (sz[0]-sz[v]) + sum - (sum_down[v]+sz[v]));
  }
}
vvi
vi in, low;
int timer;
set<int> cut_points;
vector<ii> bridges;

void dfs_ap(int u, int p = -1) {
  in[u] = low[u] = ++timer;
  int ch = 0;
  for (int v : adj[u]) {
    if (v == p) continue;
    if (in[v]) {
      // Back-edge
      low[u] = min(low[u], in[v]);
    } else {
      // Tree-edge
      dfs_ap(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= in[u] && p != -1)
        cut_points.insert(u);
      ch++;
    }
  }
  if (p == -1 && ch > 1)
    cut_points.insert(u);
}

void dfs_bridges(int u, int p = -1) {
  in[u] = low[u] = ++timer;
  for (int v : adj[u]) {
    if (v == p) continue;
    if (in[v]) {
      low[u] = min(low[u], in[v]);
    } else {
      dfs_bridges(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > in[u])
        bridges.push_back({u, v});
    }
  }
}

void init(int n) {
  timer = 0;
  in.assign(n, 0);
  low.assign(n, 0);
  cut_points.clear();
  bridges.clear();
}
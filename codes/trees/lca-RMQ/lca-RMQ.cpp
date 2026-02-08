vvi ch;
vi tin, dep, et_nodes, et_depths;
int timer = 0;
int n;

SparseTable st; // same as in this handbook

void dfs(int u) {
  et_nodes.push_back(u);
  et_depths.push_back(dep[u]);
  tin[u] = timer++;

  for (int v : ch[u]) {
      dep[v] = dep[u] + 1;
      dfs(v);
      et_nodes.push_back(u); 
      et_depths.push_back(dep[u]);
  }

  timer++;
}

int lca(int u, int v) {
  int tu = tin[u];
  int tv = tin[v];
  if (tu > tv) swap(tu, tv);
  auto [val,id] = st.min(tu,tv);
  return et_nodes[id];
}

// pre allocation and dfs call
ch = vvi(n);
tin = vi(n);
dep = vi(n);
et_nodes.reserve(2 * n); 
et_depths.reserve(2 * n); 

dfs(0); 
st.build(et_depths);

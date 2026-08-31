const int MAX = 1e6;
namespace aho {
  int next[MAX][26];
  int link[MAX], sz = 0, freq[MAX], exit[MAX];
  vi leaves[MAX], order;
  void insert(const string& pat, int id) {
    int u = 0;
    for (char c : pat) {
      int x = c - 'a';
      if (!next[u][x]) next[u][x] = ++sz;
      u = next[u][x];
    }
    leaves[u].push_back(id);
  }
  void build() {
    queue<int> q; q.push(0);
    link[0] = -1;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      order.push_back(u);
      for (int x = 0; x < 26; x++) {
        int v = next[u][x];
        if (!v) continue;
        int l = link[u];
        while (l != -1 && !next[l][x]) l = link[l];
        link[v] = l == -1 ? 0 : next[l][x];
        exit[v] = leaves[link[v]].empty() ? exit[link[v]] : link[v];
        q.push(v);
      }
    }
  }
  vi query(const string& txt, int num_patterns) {
    vi ans(num_patterns);
    int u = 0;
    for (char c : txt){
      int x = c - 'a';
      while (u != -1 && !next[u][x]) u = link[u];
      u = u == -1 ? 0 : next[u][x];
      freq[u]++;
    }
    for (int i = (int)order.size() - 1; i >= 0; i--) {
      int u = order[i];
      if (link[u] != -1) freq[link[u]] += freq[u];
    }
    for (int i = 1; i <= sz; i++)
      for (int id : leaves[i])
        ans[id] += freq[i];   
    return ans;
  }
}
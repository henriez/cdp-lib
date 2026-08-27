auto spfa = [&](int s, int n) -> pair<vi, vi> {
  vi dist(n, INF), p(n, -1), cnt(n, 0);
  vector<bool> inq(n, false), in_neg(n, false);
  queue<int> q, neg_q;
  vi cycle;
  dist[s] = 0;
  // if you need ANY neg cycle, push all vertices
  // instead of a fixed source
  q.push(s);
  inq[s] = true;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    inq[u] = false;
    for (auto [v, w] : adj[u]) {
      if (dist[v] > dist[u] + w && !in_neg[v]) {
        dist[v] = dist[u] + w;
        p[v] = u;
        cnt[v] = cnt[u] + 1;
        if (cnt[v] >= n) {
          if (cycle.empty()) {
            int c = v;
            for (int i = 0; i < n; i++) c = p[c];
            for (int cur = c; ; cur = p[cur]) {
              cycle.push_back(cur);
              if (cur == c && cycle.size() > 1) break;
            }
            reverse(all(cycle));
          }
          if (!in_neg[v]) {
            in_neg[v] = true;
            neg_q.push(v);
          }
        } else if (!inq[v]) {
          q.push(v);
          inq[v] = true;
        }
      }
    }
  }
  while (!neg_q.empty()) {
    int u = neg_q.front(); neg_q.pop();
    dist[u] = -INF;
    for (auto [v, w] : adj[u]) {
      if (!in_neg[v]) {
        in_neg[v] = true;
        neg_q.push(v);
      }
    }
  }
  // dist -INF is there is no shortest path
  return {dist, cycle};
};
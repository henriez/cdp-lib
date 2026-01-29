
// cost should be (cost[worker][job])
pair<int,vii> hungarian(int n, int m, const vvi &cost) {
  if (n == 0) return {0,{}};
  int N = max(n, m);

  vi u(N+1), v(N+1), p(N+1), way(N+1);

  const int INF = 1e9;
  for (int i = 1; i <= n; ++i) {
    p[0] = i;
    int j0 = 0;
    vi minv(N + 1, INF);
    vector<bool> used(N + 1, false);

    do {
      used[j0] = true;
      int i0 = p[j0], delta = INF, j1;

      for (int j = 1; j <= N; ++j) {
        if (!used[j]) {
          int cur = cost[i0-1][j-1] - u[i0] - v[j];
          if (cur < minv[j]) {
            minv[j] = cur;
            way[j] = j0;
          }
          if (minv[j] < delta) {
            delta = minv[j];
            j1 = j;
          }
        }
      }

      for (int j = 0; j <= N; ++j) {
        if (used[j]) {
          u[p[j]] += delta;
          v[j] -= delta;
        } else {
          minv[j] -= delta;
        }
      }
      j0 = j1;
    } while (p[j0] != 0);

    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0);
  }

  int total_cost = 0;
  for (int j = 1; j <= m; ++j) {
    if (p[j] != 0) {
      total_cost += cost[p[j] - 1][j - 1];
    }
  }

  // {worker,job}[] 0-indexed
  vii matchings;
  for (int j = 1; j <= m; ++j) {
    if (p[j] != 0) {
      matchings.push_back({p[j] - 1, j - 1});
    }
  }
  return {total_cost, matchings};
}
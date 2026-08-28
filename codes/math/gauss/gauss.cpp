pair<int, vector<ld>> gauss(vector<vector<ld>> a) {
  const double eps = 1e-6;
  int n = a.size(), m = a[0].size()-1;
  vi where(m, -1);
  for (int var = 0, eq = 0; var < m && eq < n; var++) {
    int piv = eq;
    for (int i=eq; i<n; ++i)
      if (abs(a[i][var]) > abs(a[piv][var])) piv = i;
    if (abs(a[piv][var]) < eps) continue;
    for (int i = var; i <= m; i++)
      swap(a[piv][i], a[eq][i]);
    where[var] = eq;
    for (int i = 0; i < n; i++) if (i != eq) {
      ld c = a[i][var] / a[eq][var];
      for (int j = var; j <= m; j++)
        a[i][j] -= a[eq][j] * c;
    }
    eq++;
  }

  vector<ld> ans(m, 0);
  for (int i = 0; i < m; i++) if (where[i] != -1)
    ans[i] = a[where[i]][m] / a[where[i]][i];
  for (int i = 0; i < n; i++) {
    ld sum = 0;
    for (int j = 0; j < m; j++)
      sum += ans[j] * a[i][j];
    if (abs(sum - a[i][m]) > eps) return {0,{}};
  }

  for (int i = 0; i < m; i++) if (where[i] == -1)
    return {INF,ans};
  return {1, ans};
}
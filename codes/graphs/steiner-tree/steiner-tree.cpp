int p = dsu.find(special[0]);
for (int i : special){
  if (dsu.find(i) != p){
    cout << "impossivel\n"; return;
  }
}
vvi dp(1<<s, vi(n,INF));
for (int i = 0; i < s; i++) 
  dp[1<<i][special[i]] = 0;

for (int mask = 0; mask < (1<<s); mask++){
  for (int sub = mask; sub > 0; sub = (sub-1)&mask){
    for (int u = 0; u < n; u++) {
      dp[mask][u] = min(dp[mask][u], dp[sub][u] + dp[mask^sub][u]);
    }
  }
  priority_queue<ii, vii, greater<ii>> pq;
  for (int u = 0; u < n; u++) pq.push({dp[mask][u], u});

  while(!pq.empty()){
    auto [d,u] = pq.top(); pq.pop();
    if (d > dp[mask][u]) continue;
    for (auto &[w,v] : adj[u]){
      if (dp[mask][v] > dp[mask][u] + w) {
        dp[mask][v] = dp[mask][u] + w;
        pq.push({dp[mask][v], v});
      }
    }
  }
}
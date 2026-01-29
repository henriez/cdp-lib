vvi dp(n+1,vi(W+1));
for (int c = 1; c <= W; c++){
  for (int i = 1; i <= n; i++){
    dp[i][c] = dp[i-1][w];
    if (c-w[i-1] >= 0) {
      dp[i][c] = max(dp[i][c], dp[i-1][c-w[i-1]] + v[i-1]);
    }
  }
}

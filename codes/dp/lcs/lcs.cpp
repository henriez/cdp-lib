vvi dp(n+1,vi(m+1));

for (int i = 1; i <= n; i++){
  for (int j = 1; j <= m; j++){
    if (a[i-1] == b[j-1]) {
      dp[i][j] = dp[i-1][j-1]+1;
    } else if (dp[i][j-1] > dp[i-1][j]){
      dp[i][j] = dp[i][j-1];
    } else {
      dp[i][j] = dp[i-1][j];
    }
  }
}

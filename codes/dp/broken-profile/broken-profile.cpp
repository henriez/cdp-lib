int dp[1002][12][1024];
dp[0][0][0] = 1;

for (int i = 0; i < m; i++){
  for (int j = 0; j < n; j++){
    for (int mask = 0; mask < (1<<n); mask++){
      if (mask & (1<<j)){
        int nxt_mask = mask - (1<<j);
        dp[i][j+1][nxt_mask] += dp[i][j][mask];
        dp[i][j+1][nxt_mask] %= M;
      } else {
        int q = mask + (1 << j);
        dp[i][j+1][q] += dp[i][j][mask];
        dp[i][j+1][q] %= M;
        if (j < n-1 && (mask & (1<<(j+1)))==0){
          q = mask + (1 << (j+1));
          dp[i][j+1][q] += dp[i][j][mask];
          dp[i][j+1][q] %= M;
        }
      }
    }
  }

  for (int p = 0; p < (1<<n); p++){
    dp[i+1][0][p] = dp[i][n][p];
  }
}
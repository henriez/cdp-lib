vi dp(W+1);
for (int i = 0; i < n; i++){
  for (int j = W; j >= w[i]; j--){
    dp[j] = max(dp[j], v[i] + dp[j-w[i]]);
  }
}
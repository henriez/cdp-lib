vvi dp(n+1, vi(m+1));
for (int i = 0; i <= n; i++) dp[i][0] = i;
for (int i = 0; i <= m; i++) dp[0][i] = i;
for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
        dp[i][j] = min(
            min(dp[i][j-1]+1, dp[i-1][j]+1), 
            dp[i-1][j-1]+(s[i-1]!=t[j-1])
        );
    }
}
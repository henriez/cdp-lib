vi w(n);

vector<ii> dp(1<<n, ii(INF,0));
// dp[i] = for the subset i(bitmask) (A,B) is the pair where
// A - the min number of knapsacks to store this subset
// B - the min size of a used knapsack

dp[0] = ii(0,INF);
for (int subset = 1; subset < (1<<n); subset++){
  for (int item = 0; item < n; item++){
    if (!((subset>>item)&1)) continue;
    int prevsubset = subset - (1<<item);
    ii prev = dp[prevsubset];
    
    if (prev.second + w[item] <= x) {
      // can fill the knapsack, fill it
      dp[subset] = min(dp[subset], ii(prev.first, prev.second+w[item]));
    } else {
      // cant fill the knapsack, create a new one
      dp[subset] = min(dp[subset], ii(prev.first+1, w[item]));
    }
  }
}

cout << dp[(1<<n)-1].first << endl;
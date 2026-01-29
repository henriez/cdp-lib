vvi dp(n+1,vi(sum+1));
vvii p(n+1,vii(sum+1));

dp[0][0] = 1;

for (int i = 1; i <= n; i++){
  for (int s = 1; s <= sum; s++){
    if (s-a[i-1] >= 0 && dp[i-1][s-a[i-1]]){
      // sum is possible taking item i
      p[i][s] = {i-1,s-a[i-1]}; 
      dp[i][s] = 1;
    } else if (dp[i-1][s]) {
      // sum not possible taking item i
      // but still possible with other items (<i)
      p[i][s] = {i-1,s}; 
      dp[i][s] = 1;
    }
  }
}

if (!dp[n][target]) {
  cout << -1 << endl;
  return;
}

vi subset;
ii pos = {n,target};
while(pos != ii(0,0)){
  auto [i,s] = pos;
  if (p[i][s].second != s) subset.push_back(a[i-1]);
  pos = p[i][s];
}
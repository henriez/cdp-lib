// dp[i] := min value a subsequence of length i+1 can end in
// dp is an increasing sequence, allowing for bin search
int lis(const vi &a){
  vi dp;
  for (int x : a){
    auto it = lower_bound(all(dp), x);
    if (it == dp.end()) dp.push_back(x);
    else *it = x;
  }
  return dp.size();
}

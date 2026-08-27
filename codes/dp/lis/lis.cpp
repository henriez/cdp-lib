// dp[i] := min value subseq of len i+1 can end in
// dp is increasing sequence -> BS
int lis(const vi &a){
  vi dp;
  for (int x : a){
    auto it = lower_bound(all(dp), x);
    if (it == dp.end()) dp.push_back(x);
    else *it = x;
  }
  return dp.size();
}

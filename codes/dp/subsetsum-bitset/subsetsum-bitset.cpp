vi a;
bitset<MAXSUM+1> dp; dp[0] = 1;
for (int x : a) dp |= (dp << x);
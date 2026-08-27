int n, ans = 0;
vi primes;
for (int mask = 1; mask < (1<<primes.size()); mask++){
  int prod = 1;
  for (int bit = 0; bit < primes.size(); bit++) {
    if (mask>>bit&1) {
      prod *= primes[bit];
      if (prod > n) break;
    }
  }
  if (__popcount(mask) & 1) ans += n/prod;
  else ans -= n/prod;
}

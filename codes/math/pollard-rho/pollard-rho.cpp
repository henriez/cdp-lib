u64 pollard_rho(u64 n) {
  if (n % 2 == 0) return 2;
  if (miller_rabin(n)) return n;
  static mt19937_64 rng(1337); // change to chrono
  u64 x = 0, y = 0, c = 0, prd = 1, d = 1;
  auto f = [&](u64 v) { return ((u128)v*v + c)%n; };
  while (d == 1 || d == n) {
    x = y = rng() % (n - 2) + 2;
    c = rng() % (n - 1) + 1;
    d = 1;
    for (int step = 1; d == 1; step <<= 1) {
      x = y;
      for (int i = 0; i < step; ++i) y = f(y);
      for (int k = 0; k < step && d == 1; k += 128) {
        prd = 1;
        int limit = min(step - k, 128);
        for (int i = 0; i < limit; ++i) {
          y = f(y);
          prd = (u128)prd * (x > y ? x-y : y-x)%n;
        }
        d = gcd(prd, n);
      }
    }
  }
  return d;
}
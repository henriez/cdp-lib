using u64 = uint64_t;
using u128 = __uint128_t;
u64 modpow(u64 b, u64 e, u64 mod) {
  u64 ans = 1;
  for (b %= mod; e; e >>= 1, b = (u128)b * b % mod)
    if (e & 1) ans = (u128)ans * b % mod;
  return ans;
}
// if up to 32 bits, use {2, 7, 61}
u64 primes[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool miller_rabin(u64 n) {
  if (n < 2) return false;
  if (n % 2 == 0) return n == 2;
  u64 d = n - 1;
  int s = 0;
  while (d % 2 == 0) d >>= 1, s++;
  for (u64 a : primes) {
    if (a%n == 0) continue;
    u64 x = modpow(a, d, n);
    if (x == 1 || x == n - 1) continue;
    bool composite = true;
    for (int r = 1; r < s; r++) {
      x = (u128)x * x % n;
      if (x == n - 1) { composite = false; break; }
    }
    if (composite) return false;
  }
  return true;
}
void factorize(u64 n, vector<u64>& factors) {
  if (n <= 1) return;
  if (miller_rabin(n)) {
    factors.push_back(n);
    return;
  }
  u64 divisor = pollard_rho(n);
  factorize(divisor, factors);
  factorize(n / divisor, factors);
}
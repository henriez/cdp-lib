auto sieve = [](int n) -> pair<vi,vi> {
  vi primes, mu(n+1);
  mu[1] = 1;
  vector<bool> is_prime(n+1, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      mu[i] = -1;
    }
    for (int p : primes) {
      if (i*p > n) break;
      is_prime[i*p] = false;
      if (i%p == 0) {
        mu[i*p] = 0;
        break;
      }
      mu[i*p] = -mu[i];
    }
  }
  return {primes, mu};
};
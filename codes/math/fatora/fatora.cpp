// O(sqrt(n)) fatores repetidos
vi fatora(int n) {
  vi factors;
  for (int x = 2; x*x <= n; x++) {
    while (n%x == 0) {
      factors.push_back(x);
      n /= x;
    }
  }
  if (n > 1) factors.push_back(n);
  return factors;
}
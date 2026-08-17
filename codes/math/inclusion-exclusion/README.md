# Inclusion-Exclusion Principle

For a set of $k$ primes, count numbers from $1$ to $n$ divisible by at least one prime.

For every non-empty subset of primes:

- If the subset has odd size, add $n / prod$.
- If the subset has even size, subtract $n / prod$.
- $prod$ is the product of the selected primes.

Here, $n / prod$ is the number of integers from $1$ to $n$ divisible by all selected primes.

Complexity: $\mathcal{O}(2^k k)$.
# Number Theoretic Transform (NTT)

NTT is a fast algorithm (analogous to FFT) for polynomial multiplication modulo a special prime. It requires a prime modulus $p = c \cdot 2^k + 1$ (a "primitive root prime") and a primitive $2^k$-th root of unity modulo $p$.

- **Prime Choices:** To use NTT, pick a modulus and a matching primitive root (see table below). For arbitrary moduli (e.g., $10^9+7$), multiply with several NTT-friendly primes and reconstruct with CRT (see `crt_multiply`).
- **Time Complexity:** $\mathcal{O}(n \log n)$ for polynomial multiplication.

## NTT-Friendly Primes and Roots

NTT-friendly primes and their primitive roots:

- Modulus: 998244353, Primitive Root: 3, Maximum N: $2^23$
- Modulus: 734003201, Primitive Root: 3, Maximum N: $2^20$
- Modulus: 167772161, Primitive Root: 3, Maximum N: $2^25$
- Modulus: 469762049, Primitive Root: 3, Maximum N: $2^26$

Use the modulus as `MOD` and the root as `ROOT` when instantiating the NTT.

- For large/concrete moduli, see `crt_multiply` in the code for a multi-modulus solution with Chinese Remainder Theorem (CRT).


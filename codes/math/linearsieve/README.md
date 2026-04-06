# Linear Sieve + Möbius Function

$$
\mu(n) = \begin{cases} 
1 & \text{if } n=1 \\\\
(-1)^k & \text{if } n \text{ is a product of } k \text{ distinct primes} \\\\
0 & \text{if } p^2 \mid n \text{ for some prime } p 
\end{cases}
$$

## Applications

* **Inclusion-Exclusion:** Naturally generates $1, -1, 0$ coefficients for prime factor sets.
* **Möbius Inversion:** Converts $g(n) = \sum\sb{d \mid n} f(d)$ to $f(n) = \sum\sb{d \mid n} \mu(d)g(\frac{n}{d})$. Often reduces $O(N)$ divisor sums to $O(\sqrt{N})$.
* **Dirichlet Convolution:** $\mu * \mathbf{1} = \epsilon$. Core to sub-linear prefix sum algorithms (e.g., DuSieve) yielding $O(N^{2/3})$ time.
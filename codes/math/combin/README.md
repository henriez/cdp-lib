# Combinatorics (Pascal's Triangle)
Computes "n choose k". Requires factorials to be pre-computed.
Time: $\mathcal{O}(\log ZAP)$

## Combinatorial Analysis

### Fundamental Counting Principles
- **Permutations:** The number of ways to arrange $k$ items from a set of $n$ distinct items.
$$P(n, k) = \frac{n!}{(n-k)!}$$

- **Combinations (Binomial Coefficient):** The number of ways to choose $k$ items from a set of $n$ distinct items, regardless of order.
$$\binom{n}{k} = C(n, k) = \frac{n!}{k!(n-k)!}$$

- **Combinations with Repetition (Stars and Bars):** The number of ways to choose $k$ items of $n$ types, allowing repetitions. Equivalently, the number of ways to distribute $k$ identical balls into $n$ distinct urns.
$$\binom{k+n-1}{n-1} = \binom{k+n-1}{k}$$

### Binomial Coefficient Properties and Pascal's Triangle

- **Pascal's Triangle**
$$
\[
\begin{aligned}
n=0:& \quad \binom{0}{0} \\
n=1:& \quad \binom{1}{0} \quad \binom{1}{1} \\
n=2:& \quad \binom{2}{0} \quad \binom{2}{1} \quad \binom{2}{2} \\
n=3:& \quad \binom{3}{0} \quad \binom{3}{1} \quad \binom{3}{2} \quad \binom{3}{3} \\
n=4:& \quad \binom{4}{0} \quad \binom{4}{1} \quad \binom{4}{2} \quad \binom{4}{3} \quad \binom{4}{4} \\
n=5:& \quad \binom{5}{0} \quad \binom{5}{1} \quad \binom{5}{2} \quad \binom{5}{3} \quad \binom{5}{4} \quad \binom{5}{5}
\end{aligned}
\]
$$


- **Stifel's Relation:** Each element in Pascal's Triangle is the sum of the two elements immediately above it.
$$\binom{n}{k} = \binom{n-1}{k} + \binom{n-1}{k-1}$$

- **Symmetry:** Elements of a row are symmetric with respect to the center. Choosing $k$ elements is the same as choosing the $n-k$ elements to be left behind.
$$\binom{n}{k} = \binom{n}{n-k}$$

- **Row Sum:** The sum of all elements in row $n$ of Pascal's Triangle (where the first row is $n=0$) is equal to $2^n$.
$$\sum_{k=0}^{n} \binom{n}{k} = 2^n$$

- **Hockey Stick Identity:** The sum of elements in a diagonal, starting at $$\binom{r}{r}$$ and ending at $$\binom{n}{r}$$, is equal to the element in the next row and next column, $$\binom{n+1}{r+1}$$.
$$\sum_{i=r}^{n} \binom{i}{r} = \binom{n+1}{r+1}$$

- **Binomial Theorem:**
$$(x+y)^n = \sum_{k=0}^{n} \binom{n}{k} x^{n-k} y^k$$

- **Vandermonde's Identity:**
$$\sum_{j=0}^{k} \binom{m}{j}\binom{n}{k-j} = \binom{m+n}{k}$$
The easiest way to understand the identity is through a counting problem. \\
Imagine you have a committee with m men and n women. How many ways can you form a subcommittee of k people?

**Way 1** Direct Counting

You have a total of m+n people and need to choose k of them. The number of ways to do this is simply:
 $$\binom{m+n}{k}$$

**Way 2** Counting by Cases

We can divide the problem into cases, based on how many men ($j$) are chosen for the subcommittee.
    Case 0: Choose 0 men and k women. The number of ways is  $$\binom{m}{0}\binom{n}{k}$$.
    
    Case 1: Choose 1 man and k-1 women. The number of ways is $$\binom{m}{1}\binom{n}{k-1}$$.
    Case j: Choose $j$ men and $k-j$ women. The number of ways is $$\binom{m}{j}\binom{n}{k-j}$$.



### Other Important Concepts
- **Catalan Numbers:** A sequence of natural numbers that occurs in various counting problems (e.g., number of binary trees, balanced parenthesis expressions).
$$C_n = \frac{1}{n+1}\binom{2n}{n}$$

- **Stirling Numbers of the Second Kind:** The number of ways to partition a set of $n$ labeled objects into $k$ non-empty unlabeled subsets. Denoted by $S(n, k)$ or $$\begin{Bmatrix} n \\ k \end{Bmatrix}$$.
$$S(n, k) = \frac{1}{k!} \sum_{j=0}^{k} (-1)^{k-j} \binom{k}{j} j^n$$

- **Pigeonhole Principle:** If $n$ items are put into $m$ boxes, with $n > m$, then at least one box must contain more than one item.

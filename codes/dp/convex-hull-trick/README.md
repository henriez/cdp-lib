# Convex Hull Trick (CHT)

* **Recurrence form:**

  $$
  dp\sb{i} = \min\sb{j<i}
  \left(dp\sb{j} + (h\sb{i} - h\sb{j})^2 + c\right)
  $$

  Expanding:

  $$
  dp\sb{i} = h\sb{i}^2 + c +
  \min\sb{j<i}
  \left((-2h\sb{j})h\sb{i} + h\sb{j}^2 + dp\sb{j}\right)
  $$

  Thus, for each $j$, insert the line

  $$
  f\sb{j}(x) = (-2h\sb{j})x + h\sb{j}^2 + dp\sb{j}
  $$

  and query at $x=h\sb{i}$.

  
  
* **Slope monotonicity:**
  If coefficients $a\sb{j}$ (slopes) are inserted in strictly decreasing (or increasing) order as $j$ grows, and

* **Query monotonicity:**
  Values $x\sb{i}$ for query come in non-decreasing (min) or increasing (max) order consistent with slope order,

* **Complexity:**
    * Insertion + amortized query in $\mathcal{O}(1)$ per operation (pointer walk) under monotonicity.
    * Non-monotonic case, generic CHT via binary search: $\mathcal{O}(\log n)$ per query.
    * General alternative: Li Chao Tree for insertions/queries in arbitrary order, $\mathcal{O}(\log M)$ per operation (where $M$ is the domain of $x$).

* **Constraints:**
    * If it cannot be written in linear form, CHT does not apply.
    * If there is no monotonicity of slopes or queries, consider Li Chao Tree or CHT variant with binary search.

The example below solves the $dp$ where the recurrence is:

$$
dp\sb{i} = \min\sb{j<i}
\left(dp\sb{j} + (h\sb{i} - h\sb{j})^2 + c\right).
$$
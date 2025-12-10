# Knapsack - 1D
The spirit here is the same as the 2D version, but here it iterates on the knapsack capacity backwards, to ensure that the value of \lstinline{dp[j-w[i]]} is not considering the item \lstinline{i}.
Time: $\mathcal{O}(nW)$
Space: $\mathcal{O}(W)$
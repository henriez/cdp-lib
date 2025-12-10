# LCA - RMQ
Pre-computation: $\mathcal{O}(n\log n)$
Queries: $\mathcal{O}(1)$
OBS: call first $dfs(root)$ and then $buildSparseTable()$ before making queries. Also remember to call $euler_tour_nodes.reserve(2\cdot n)$ and $euler_tour_depths.reserve(2\cdot n)$ to optimize memory allocation time of $push_back$.
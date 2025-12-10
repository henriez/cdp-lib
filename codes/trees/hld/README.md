# HLD - Heavy light decomposition
If you need to compute a function on a path in a tree and need to support value updates on nodes, HLD is the way.
Pre-computation: $\mathcal{O}(n)$
Queries: $\mathcal{O}(\log^2n)$

OBS: this implementation uses the same segtree as this notebook, with 0-indexing and open-closed interval convention. Ideally, just change the segtree to change the computed function, the HLD struct remains the same.
\\
OBS2: this template also supports mass updates (path/subtree) and subtree queries.
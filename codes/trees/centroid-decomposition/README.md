# Centroid Decomposition

Recursively splits a tree by its center of mass, building a "Centroid Tree" with a strictly guaranteed $O(\log N)$ depth. Used for path queries where the tree is unrooted.

**Build:** $O(N \log N)$

Sample is solving "count distinct paths with number of edges between $k\sb1$ and $k\sb2$"
# Segment Tree

You should (almost) never alter the `segtree` logic. Ideally you only modify the `node` struct by answering four questions:

1.  **`tag`**: What data does a range update carry? (e.g., a single integer for addition, or a pair of integers $\{a, d\}$ for an AP).
2.  **`apply()`**: How does a `tag` mathematically alter the state of a single node?
3.  **`push()`**: How does a parent node transfer its pending `tag` to its `left` and `right` children?
4.  **`combine()`**: How do you calculate the state of a parent by merging the states of its children?

OBS: lazy segtrees must be called with `has=true`
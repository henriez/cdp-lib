# Segment Tree

## Iterative Point Update
**Best for:** Standard point updates and range queries (e.g., Point Add + Range Sum).

-   **Performance:** Best possible.
-   **Memory:** Best possible: $2n$ allocation.
-   **Use Case:** If no range updates, then use this.

## Iterative Lazy
**Best for:** Index-independent range updates (e.g., Range Add, Range Set, Range Max, Range Flip).

-   **Performance:** Noticeably faster than recursive lazy trees.
-   **Index Blindness:** If the update depends on the range indexes themsleves (such as AP addition), use the recursive lazy one.

## Recursive Lazy
**Best for:** Index-dependent updates (e.g. AP addition), Tree Walking (Binary Search on Tree), and persistency.

-   **Performance:** It is the slowest of the three, use only if necessary.

## Usage

You should (almost) never alter the `segtree` logic. Ideally you only modify the `node` struct by answering four questions:

1.  **`tag`**: What data does a range update carry? (e.g., a single integer for addition, or a pair of integers $\{a, d\}$ for an AP).
2.  **`apply()`**: How does a `tag` mathematically alter the state of a single node?
3.  **`push()`**: How does a parent node transfer its pending `tag` to its `left` and `right` children?
4.  **`combine()`**: How do you calculate the state of a parent by merging the states of its children?
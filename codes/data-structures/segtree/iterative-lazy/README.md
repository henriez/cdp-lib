# Iterative Lazy
**Best for:** Index-independent range updates (e.g., Range Add, Range Set, Range Max, Range Flip).

-   **Performance:** Noticeably faster than recursive lazy trees.
-   **Index Blindness:** If the update depends on the range indexes themsleves (such as AP addition), use the recursive lazy one.

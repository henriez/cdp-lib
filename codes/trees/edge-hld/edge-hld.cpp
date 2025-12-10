
struct EdgeHLD {
    int n, timer = 0;
    vvii adj;
    vi parent, depth, size, heavy, head, value;
    vi tin, tout;
 
    segtree seg;
 
    void init(int _n, vvii& _adj) {
        n = _n;
        adj = _adj;
        value.assign(n, 0);
        parent.assign(n, -1);
        depth.assign(n, 0);
        size.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        timer = 0;

        // edgeWeight[v] = weight of edge (parent[v], v), for v>0
        // root (0) has no parent, so its value is dummy (0)

        dfs1(0,0,0);
        dfs2(0, 0);
 
        vi linear(n);
        for (int u = 0; u < n; u++)
            linear[tin[u]] = value[u]; // position stores edge weight
 
        seg.init(linear);
    }
 
    int dfs1(int u, int p, int w) {
        size[u] = 1;
        parent[u] = p;
        value[u] = w;
        int max_sz = 0;
        for (auto[v,w] : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            int sz = dfs1(v, u, w);
            size[u] += sz;
            if (sz > max_sz) {
                max_sz = sz;
                heavy[u] = v;
            }
        }
        return size[u];
    }
 
    void dfs2(int u, int h) {
        tin[u] = timer++;
        head[u] = h;
        if (heavy[u] != -1)
            dfs2(heavy[u], h);
        for (auto [v,w] : adj[u]) {
            if (v != parent[u] && v != heavy[u])
                dfs2(v, v);
        }
        tout[u] = timer;
    }

    // u deve ser o filho
    void update_edge(int u, int val) {
        seg.set(tin[u], val);
    }

    void rangeUpdate(int u, int v, int x) {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            seg.rangeUpdate(tin[head[u]], tin[u] + 1, x);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        seg.rangeUpdate(tin[u] + 1, tin[v] + 1, x); // +1 to skip LCA's edge
    }

    void update_subtree(int u, int x) {
        // updates all edges in subtree of u (skip incoming edge to u)
        seg.rangeUpdate(tin[u] + 1, tout[u], x);
    }
 
    segtree::node query(int u, int v) {
        segtree::node res = seg.NEUTRAL;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            res = seg.merge(res, seg.query(tin[head[u]], tin[u] + 1));
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        res = seg.merge(res, seg.query(tin[u] + 1, tin[v] + 1)); // skip LCA's edge
        return res;
    }
 
    segtree::node query_subtree(int u) {
        // query all edges in subtree of u
        return seg.query(tin[u] + 1, tout[u]);
    }
};
struct DSU {
    vi p, sz;
    DSU(int n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        sz.assign(n, 1);
    }
    int find(int i) {
        if (p[i] == i) return i;
        return p[i] = find(p[i]);
    }
    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        p[v] = u;
        sz[u] += sz[v];
        return true;
    }
};
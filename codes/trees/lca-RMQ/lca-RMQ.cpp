int n, timer = 0;
vi tin, dep, euler_tour_nodes, euler_tour_depths;
vvi ch;
vvii sparse_table;

void dfs(int u) {
    euler_tour_nodes.push_back(u);
    euler_tour_depths.push_back(dep[u]);
    tin[u] = timer++;

    for (int v : ch[u]) {
        dep[v] = dep[u] + 1;
        dfs(v);
        euler_tour_nodes.push_back(u); 
        euler_tour_depths.push_back(dep[u]);
    }

    timer++;
}

void buildSparseTable() {
    int m = euler_tour_depths.size();
    sparse_table.assign(LOGN, vii(m)); 

    for (int i = 0; i < m; i++) {
        sparse_table[0][i] = {euler_tour_depths[i], i};
    }

    for (int i = 1; (1 << i) <= m; i++) {
        int len = 1<<i;
        for (int time = 0; time+len <= m; time++) {
            ii ans1 = sparse_table[i-1][time];
            ii ans2 = sparse_table[i-1][time + len/2];
            sparse_table[i][time] = min(ans1, ans2);
        }
    }
}

int lca(int u, int v) {
    int tu = tin[u];
    int tv = tin[v];
    if (tu > tv) swap(tu, tv);

    int k = __bit_width((tv - tu + 1)) - 1;

    ii ans1 = sparse_table[k][tu];
    ii ans2 = sparse_table[k][tv - (1 << k) + 1];

    if (ans1.first <= ans2.first) {
        return euler_tour_nodes[ans1.second];
    }
    return euler_tour_nodes[ans2.second];
}
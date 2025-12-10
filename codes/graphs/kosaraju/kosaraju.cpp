void dfs1(int u){
    vis[u] = 1;
    for (auto v : adj[u]){
        if (!vis[v]) dfs1(v);
    }

    ts.push_back(u);
}

void dfs2(int u, int c){
    scc[u] = c;
    for (auto v : adjT[u])
        if (!scc[v]) dfs2(v,c);
}


// usage
for (int i = 0; i < n; i++)
    if (!vis[i]) dfs1(i);

reverse(ts.begin(), ts.end());

int c = 1;
for (auto u : ts)
    if (!scc[u]) dfs2(u,c++);
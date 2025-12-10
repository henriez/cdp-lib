vvi adj, up;
vi tin, tout;
int timer = 0;

void dfs(int u, int p){
    tin[u] = timer++;
    for (auto v : adj[u]){
        if (v == p) continue;
        up[v][0] = u;
        for (int dist = 1; dist < LOGN; dist++){
            up[v][dist] = up[up[v][dist-1]][dist-1];
        }
        dfs(v);
    }
    tout[u] = timer++;
}

int isAncestor(int u, int v){
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v){
    if (isAncestor(u,v)) return u;
    if (isAncestor(v,u)) return v;
    for (int dist = LOGN-1; dist >= 0; dist--){
        if(!isAncestor(up[u][dist],v)) u = up[u][dist];
    }
    return up[u][0];
}
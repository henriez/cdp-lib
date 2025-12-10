vi d;
vi_ii e;
vi ans;

int merged;
vi _p, _leaf, _wei;
vvi adj;
int _find(int u) { return _p[u] == u ? u: _p[u] = _find(_p[u]); }
void _union(int u, int v, int w){
    u = _find(u);
    v = _find(v);
    int merge_ind = merged+n;
    _p[u] = merge_ind;
    _p[v] = merge_ind;
    _leaf[merge_ind] = _leaf[u] + _leaf[v];
    _wei[merge_ind] = max(_wei[u], _wei[v]);
    adj[u].push_back(merge_ind);
    adj[merge_ind].push_back(u);
    adj[v].push_back(merge_ind);
    adj[merge_ind].push_back(v);
    merged++;
}
void make(){
    _p = vi(2*n);
    for(int i = 0; i < 2*n; i++) _p[i] = i;
    _leaf = vi(2*n, 1);
    _wei = vi(2*n);
    for(int i = 0; i < n; i++) _wei[i] = d[i];
    merged = 0;
    adj = vvi(2*n);
}

void dfs(int u, int p){
    for(auto &v: adj[u]){
        if(v == p) continue;
        ans[v] = ans[u] + (_leaf[u] - _leaf[v])*_wei[u];
        dfs(v, u);
    }
}
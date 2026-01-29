// para adicionar negacao usar ~u
// Ex: a clausula (a v !b) se traduz para add_or(a,~b)
struct TwoSatSolver {
    int n;
    vvi adj, adjT;
    vector<bool> vis, assignment;
    vi topo, scc;

    void build(int _n){
        n = 2*_n;
        adj.assign(n,vi());
        adjT.assign(n,vi());
    }

    int get(int u){
        if (u < 0) return 2*(~u)+1;
        else return 2*u;
    }

    // u -> v
    void add_impl(int u, int v){
        u = get(u), v = get(v);
        adj[u].push_back(v);
        adjT[v].push_back(u);
        adj[v^1].push_back(u^1);
        adjT[u^1].push_back(v^1);
    }

    // u || v
    void add_or(int u, int v){
        add_impl(~u, v);
    }

    // u && v
    void add_and(int u, int v){
        add_or(u,u); add_or(v,v);
    }

    // u ^ v (equiv of x != v)
    void add_xor(int u, int v){
        add_impl(u, ~v);
        add_impl(~u, v);
    }

    // u == v
    void add_equals(int u, int v){
        add_impl(u, v); 
        add_impl(v, u);
    }

    void toposort(int u){
        vis[u] = true;
        for (int v : adj[u])
            if (!vis[v]) toposort(v);
        topo.push_back(u);
    }

    void dfs(int u, int c){
        scc[u] = c;
        for (int v : adjT[u])
            if (!scc[v]) dfs(v,c);
    }

    pair<bool, vector<bool>> solve(){
        topo.clear();
        vis.assign(n, false);

        for (int i = 0; i < n; i++)
            if (!vis[i]) toposort(i);

        reverse(topo.begin(), topo.end());

        scc.assign(n, 0);
        int c = 0;
        for (int u : topo)
            if (!scc[u]) dfs(u,++c);
        
        assignment.assign(n/2, false);
        for (int i = 0; i < n; i += 2){
            if (scc[i] == scc[i+1]) return {false, {}};
            assignment[i/2] = scc[i] > scc[i+1];
        }

        return {true, assignment};
    }
};

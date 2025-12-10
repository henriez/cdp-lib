struct Dinic {
    struct Edge {
        int u, v;
        ll cap, flow = 0;
        Edge(int u, int v, ll cap) : u(u), v(v), cap(cap) {}
    };

    const ll flow_inf = 1e18;
    vector<Edge> edges;
    vvi adj;
    int n, m = 0;
    int s, t;
    vi level, ptr;
    queue<int> q;

    Dinic(int n): n(n) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int u, int v, ll cap) {
        edges.emplace_back(u,v,cap);
        edges.emplace_back(v,u,0);
        adj[u].push_back(m++);
        adj[v].push_back(m++);
    }

    bool bfs(ll delta){
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for (int id : adj[u]){
                auto &e = edges[id];
                if (e.cap - e.flow < delta) continue;
                if (level[e.v] != -1) continue;
                level[e.v] = level[u]+1;
                q.push(e.v);
            }
        }
        return level[t] != -1;
    }

    ll dfs(int u, ll pushed) {
        if (pushed == 0) return 0;
        if (u == t) return pushed;
        for (int &cid = ptr[u]; cid < (int)adj[u].size(); cid++){
            int id = adj[u][cid];
            auto &e = edges[id];
            if (level[u]+1 != level[e.v]) continue;
            ll tr = dfs(e.v,min(pushed, e.cap - e.flow));
            if (tr == 0) continue;
            e.flow += tr;
            edges[id^1].flow -= tr;
            return tr;
        }
        return 0;
    }

    ll maxflow(int s, int t){
        this->s = s; this->t = t;
        ll max_c = 0;
        for (auto &e : edges) max_c = max(max_c, e.cap);

        ll delta = 1;
        while(delta <= max_c) delta <<= 1;
        delta >>= 1;

        ll f = 0;
        for (;delta > 0; delta >>= 1){
            while(true){
                fill(level.begin(), level.end(),-1);
                level[s] = 0;
                if (!bfs(delta)) break;
                fill(ptr.begin(), ptr.end(), 0);
                while(ll pushed = dfs(s,flow_inf)) f += pushed;
            }
        }
        return f;
    }

    // call constructor with (n1+n2+2) beforehand (dont add edges manually)
    // assumes pairs are 1-indexed
    vii maxmatchings(int n1, int n2, const vii& pairs){
        for (int i = 1; i <= n1; i++)
            add_edge(0,i,1);
        
        for (int i = 1; i <= n2; i++)
            add_edge(i+n1,n-1,1);

        for (auto &[u,v] : pairs)
            add_edge(u,v+n1,1);

        maxflow(0,n-1);

        vii matchings;
        for (auto &e : edges){
            if (e.u >= 1 && e.u <= n1 && e.flow == 1 && e.v > n1){
                matchings.emplace_back(e.u,e.v-n1);
            }
        }
        return matchings;
    }

        
    vii mincut(int s, int t){
        maxflow(s,t);
        queue<int> q; q.push(s);
        vector<bool> reachable(n);
        reachable[s] = true;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for (auto &id : adj[u]){
                int v = edges[id].v;
                if (edges[id].cap - edges[id].flow > 0 && !reachable[v]) {
                    reachable[v] = true;
                    q.push(v);
                }
            }
        }
        
        vii minCutEdges;
        
        for (int i = 0; i < m; i += 2) {
            const Edge& edge = edges[i];
            if (reachable[edge.u] && !reachable[edge.v]) {
                minCutEdges.emplace_back(edge.u, edge.v);
            }
        }

        return minCutEdges;
    }
};
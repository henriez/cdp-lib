vvii adj, mst;
vi taken;

int prim(){
    priority_queue<iii, vector<iii>, greater<iii>> pq;
    taken[0] = 1;
    for (auto [w,v] : adj[0]){
        if (!taken[v]) pq.push({w, {0,v}});
    }

    int cost = 0;
    while (!pq.empty()){
        auto [w,pu] = pq.top(); pq.pop();
        auto [p,u] = pu;
        if (!taken[u]) {
            cost += w;
            mst[p].emplace_back(w,u);
            mst[u].emplace_back(w,p);
            taken[u] = 1;
            for (auto [w,v] : adj[u]){
                if (!taken[v]) {
                    pq.push({w,{u,v}});
                }
            }
        }
    }
    return cost;
}

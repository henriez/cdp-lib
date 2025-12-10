void dijkstra(int s){
    int d, u, v;
    dist = vi(n, INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.emplace(0,s);
    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto &[w,v] : adj[u]){
            if (dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
}
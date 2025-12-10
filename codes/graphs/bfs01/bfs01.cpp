vi bfs01(int s){
    vi d(n, INF);
    d[s] = 0;
    deque<int> q;
    q.push_front(s);
    while(!q.empty()){
        int u = q.front(); q.pop_front();
        for (auto [w,v] : adj[u]){
            if (d[u]+w < d[v]){
                d[v] = d[u] + w;
                if (w == 1) q.push_back(v);
                else q.push_front(v);
            }
        }
    }
    return d;
}
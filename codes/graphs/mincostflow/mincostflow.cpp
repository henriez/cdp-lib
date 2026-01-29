struct MinCostFlow {
  struct Edge {
    int to, capacity, rev;
    ll cost;
  };
 
  int n;
  vector<vector<Edge>> adj;
 
  MinCostFlow(int _n) : n(_n), adj(_n) {}
 
  void add_edge(int from, int to, int cap, ll cost){
    adj[from].push_back({to,cap,(int)adj[to].size(), cost});
    adj[to].push_back({from,0,(int)adj[from].size()-1, -cost});
  }
 
  // O(FElog(V))
  lli min_cost_flow(int s, int t, int targetFlow) {
    int flow = 0;
    ll total_cost = 0;
    vll dist, h(n);
    vi pv, pe;
 
    // needed only if negative costs exists
    spfa(s, h, pv, pe);
 
    while (flow < targetFlow) {
      dijkstra(s, h, dist, pv, pe);
 
      if (dist[t] == INF) break;
 
      for (int i = 0; i < n; i++) {
        if (dist[i] < INF) {
          h[i] += dist[i];
        }
      }
 
      int f = targetFlow - flow;
      int cur = t;
      while (cur != s) {
        f = min(f, adj[pv[cur]][pe[cur]].capacity);
        cur = pv[cur];
      }
 
      flow += f;
      total_cost += f * h[t];
      cur = t;
      while (cur != s) {
        Edge &e = adj[pv[cur]][pe[cur]];
        e.capacity -= f;
        adj[e.to][e.rev].capacity += f;
        cur = pv[cur];
      }
    }
 

    return {total_cost, flow};
  }
 
  // needed only if negative costs exists
  void spfa(int s, vll &dist, vi &pv, vi &pe) {
    dist.assign(n, INF);
    pv.assign(n,-1);
    pe.assign(n,-1);
    vector<bool> inq(n, false);
    queue<int> q;
 
    dist[s] = 0;
    q.push(s);
    inq[s] = true;
 
    while (!q.empty()) {
      int u = q.front(); q.pop();
      inq[u] = false;
      for (int i = 0; i < adj[u].size(); i++) {
        Edge &e = adj[u][i];
        int v = e.to;
        if (e.capacity > 0 && dist[v] > dist[u] + e.cost) {
          dist[v] = dist[u] + e.cost;
          pv[v] = u;
          pe[v] = i;
          if (!inq[v]) {
            inq[v] = true;
            q.push(v);
          }
        }
      }
    }
  } 
 
  void dijkstra(int s, vll &h, vll &dist, vi &pv, vi &pe) {
    dist.assign(n, INF);
    pv.assign(n, -1);
    pe.assign(n, -1);
    dist[s] = 0;
 
    priority_queue<lli, vector<lli>, greater<lli>> pq;
    pq.emplace(0, s);
 
    while (!pq.empty()) {
      auto [d, u] = pq.top(); pq.pop();
      if (d > dist[u]) continue;
 
      for (int i = 0; i < adj[u].size(); i++) {
        Edge &e = adj[u][i];
        if (e.capacity <= 0) continue;
        int v = e.to;
 
        ll reduced_cost = e.cost + h[u] - h[v];
        if (dist[u] != INF && dist[v] > dist[u] + reduced_cost) {
          dist[v] = dist[u] + reduced_cost;
          pv[v] = u;
          pe[v] = i;
          pq.push({dist[v], v});
        }
      }
    }
  }
};

// usage
int nodes = 302; // amount of nodes in the network
MinCostFlow mcf(nodes);

for (int i = 0; i < 150; i++){
  mcf.add_edge(0, i+1, 1, 0); // source to node
  mcf.add_edge(i+151, nodes-1, 1, 0); // node to sink
}

for (int i = 0; i < n; i++){
  int a, b, c; cin >> a >> b >> c;
  mcf.add_edge(a, b+150, 1, -c); // edges in between (-c to maximize the cost)
}

// final max cost is -cost
auto [cost, flow] = mcf.min_cost_flow(0,nodes-1,150);
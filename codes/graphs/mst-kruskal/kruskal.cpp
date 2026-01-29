vector<pair<int,ii>> edges; // [weight, (u,v)]
int kruskal(int n){
    int cost = 0;
    DSU dsu(n); // n is the numb of vertices
    sort(edges.begin(), edges.end());
    for (auto &[w,uv] : edges){
        auto [u,v] = uv;
        if (dsu.unite(u,v)) cost += w;
    }
    return cost;
}
  
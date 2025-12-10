vector<pair<int,ii>> edges;
int kruskal(){
    int cost = 0;
    for (int i = 0; i < n; i++) {_p[i]=i; _rank[i]=0;}
    sort(edges.begin(), edges.end());
    for (auto &[w,uv] : edges){
        auto [u,v] = uv;
        if (_find(u) != _find(v)){
            cost += w;
            _union(u, v);
        }
    }
  
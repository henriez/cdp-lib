struct CentroidDecomposition{
  vvi t, ct;
  vi sz, added, cp;
  int n, root;
  CentroidDecomposition(const vvi &adj, int _k1, int _k2) 
  {
    t = adj, 
    n = adj.size();
    cp = sz = added = vi(n);
    root = -1;
    ct.resize(n);
    init(_k1, _k2);
    decompose(0,-1);
  }
  int dfs(int u, int p){
    sz[u] = 1;
    for (int v : t[u]){
      if (v == p || added[v]) continue;
      sz[u] += dfs(v,u);
    }
    return sz[u];
  }
  int centroid(int u, int size, int p = -1){
    for (int v : t[u]){
      if (v == p || added[v]) continue;
      if (2*sz[v] > size) return centroid(v,size,u);
    }
    return u;
  }
  void decompose(int u, int p){
    int size = dfs(u,p);
    int c = centroid(u,size);
    added[c] = 1;

    if (p == -1) root = c;
    else ct[p].push_back(c);
    cp[c] = p;

    process_centroid(c);

    for (int v : t[c])
      if (!added[v])
        decompose(v,c);
  }

  // custom stuff
  int k1, k2;
  ll ans;
  vi freq, distfreq;
  void init(int _k1, int _k2){
    ans = 0;
    k1 = _k1; k2 = _k2;
    distfreq = freq = vi(k2+1);
    freq[0] = 1;
  }
  void process_centroid(int c){
    int maxd = 0;
    int validsum = 0;
    for (int u : t[c]) if (!added[u]){
      distfreq[0] = 1;
      int mxd = 0;
      auto getdist = [&](auto &&getdist, int u, int p, int d) -> void {
        distfreq[d]++;
        mxd = max(mxd,d);
        if (d == k2) return;
        for (int v : t[u]){ 
          if (v == p || added[v]) continue;
          getdist(getdist,v,u,d+1);
        }
      }; getdist(getdist,u,c,1);
      int sum = validsum;
      for (int d = 1; d <= mxd; d++){
        ans += 1ll*sum*distfreq[d];
        sum -= freq[k2-d];
        if (k1-d-1 >= 0) sum += freq[k1-d-1];
      }
      for (int d = 1; d <= mxd; d++) {
        if (k1 <= d) validsum += distfreq[d];
        freq[d]+=distfreq[d], distfreq[d] = 0;
      }
      maxd = max(maxd,mxd);
    }
    for (int i = 1; i <= maxd; i++) freq[i] = 0;
  }
};
struct segtree {
  struct node {
    int seg, pre, suf, sum;
  };
  int size;
  vector<node> nodes;
  vector<bool> hasLazy;
  vector<int> lazy;

  node NEUTRAL = {0,0,0,0};

  void debug(){
    if (nodes.empty() || size == 0) {
      cout << "[Empty Tree]\n"; return;
    } 

    string indent = "..";
    function<void(int, int, int, string)> print_dfs;

    print_dfs = [&](int x, int lx, int rx, string prefix) {
      cout << prefix << " [" << lx << ", " << rx << ") ";
      
      // debug node
      node a = nodes[x];
      cout << "{ ";
      cout << "seg: " << a.seg << ' ';
      cout << "pre: " << a.pre << ' ';
      cout << "suf: " << a.suf << ' ';
      cout << "sum: " << a.sum << ' ';
      cout << "hasLazy: " << hasLazy[x] << ' ';
      cout << "lazy: " << lazy[x] << ' ';
      cout << "}";
      cout << endl;

      if (rx-lx <= 1) return;

      int mx = (lx+rx)/2;
      print_dfs(2*x+1,lx,mx, prefix + indent);
      print_dfs(2*x+2,mx,rx, prefix + indent);
    };
    print_dfs(0, 0, size, "");
  }

  node single(int v){
    return {v,v,v,v};
  }

  node merge(node a, node b){
    return {
      max(max(a.seg, b.seg), a.suf + b.pre),
      max(a.pre, a.sum + b.pre),
      max(b.suf, b.sum + a.suf),
      a.sum+b.sum
    };
  }

  void init (vi &a){
    int n = a.size();
    size = 1;
    while (size < n) size *= 2;
    nodes.assign(2*size-1, NEUTRAL);
    hasLazy.assign(2*size-1, false);
    lazy.assign(2*size-1, 0);
    build(0,0,size,a);
  }

  void build(int x, int lx, int rx, vi &a){
    if (rx-lx == 1){
      if (lx < a.size()) nodes[x] = single(a[lx]);
      return;
    }
    int mx = (lx+rx)/2;
    build(2*x+1,lx,mx,a);
    build(2*x+2,mx,rx,a);
    nodes[x] = merge(nodes[2*x+1], nodes[2*x+2]);
  }

  void set(int i, int v, int x, int lx, int rx){
    if (rx-lx == 1){
      nodes[x] = single(v);
      return;
    }
    int mx = (lx+rx)/2;
    if (i < mx) set(i, v, 2*x+1, lx, mx);
    else set(i, v, 2*x+2, mx, rx);
    nodes[x] = merge(nodes[2*x+1], nodes[2*x+2]);
  }

  void set(int i, int v){
    set(i, v, 0, 0, size);
  }

  void rangeUpdate(int l, int r, int v){
    rangeUpdate(l,r,v,0,0,size);
  }

  void rangeUpdate(int l, int r, int v, int x, int lx, int rx){
    unlazy(x,lx,rx);
    if (rx-lx < 1 || rx <= l || lx >= r) return;
    if (l <= lx && rx <= r) return propagate(x,lx,rx,v);
    int mx = (lx+rx)/2;
    rangeUpdate(l,r,v,2*x+1,lx,mx);
    rangeUpdate(l,r,v,2*x+2,mx,rx);
    nodes[x] = merge(nodes[2*x+1], nodes[2*x+2]);
  }

  node query(int l, int r){
    return query(l,r,0,0,size);
  }

  node query(int l, int r, int x, int lx, int rx){
    unlazy(x,lx,rx);
    if (rx-lx < 1 || rx <= l || lx >= r) return NEUTRAL;
    if (l <= lx && rx <= r) return nodes[x];
    int mx = (lx+rx)/2;
    node left = query(l,r,2*x+1,lx,mx);
    node right = query(l,r,2*x+2,mx,rx);
    return merge(left,right);
  }

  void unlazy(int x, int lx, int rx){
    if (hasLazy[x]){
      propagate(x,lx,rx,lazy[x]);
      hasLazy[x] = false;
    }
  }

  void propagate(int x, int lx, int rx, int v){
    nodes[x].sum = (rx-lx)*v;
    nodes[x].seg = max((rx-lx)*v,0ll);
    nodes[x].pre = max((rx-lx)*v,0ll);
    nodes[x].suf = max((rx-lx)*v,0ll);
    if (rx-lx > 1){
      lazy[2*x+1] = v;
      lazy[2*x+2] = v;
      hasLazy[2*x+1] = true;
      hasLazy[2*x+2] = true;
    }
  }
};

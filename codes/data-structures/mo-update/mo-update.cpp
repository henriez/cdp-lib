struct MoUpdate {
  int n;
  const int block_sz;
  struct Query {
    int l,r,t,id;
  };
  vector<Query> queries;
  vector<ii> updates;
  vector<int> a;

  MoUpdate(vector<int> &v, int q) : block_sz(round(cbrt(2*v.size()*v.size()))) {
    n = v.size() + q;
    a = v;
    init();
  }
  void add_query(int l, int r) {
    queries.push_back({l,r,(int)updates.size(),(int)queries.size()});
  }
  void add_update(int i, int x) {
    updates.push_back({i,x});
  }
  void update(int l, int r, int t) {
    auto &[i,v] = updates[t];
    if (l <= i && i <= r) remove(i);
    swap(a[i],v);
    if (l <= i && i <= r) add(i);
  }
  vector<int> run() {
    vector<int> ans(queries.size());
    sort(queries.begin(),queries.end(), [&](Query qa, Query qb){
      int l = qa.l/block_sz;
      int r = qa.r/block_sz;
      int ql = qb.l/block_sz;
      int qr = qb.r/block_sz;
      using iii = tuple<int,int,int>;
      return iii(l, l&1 ? -r:r, r&1 ? qa.t:-qa.t) <
        iii(ql, ql&1 ? -qr:qr, qr&1 ? qb.t:-qb.t);
    });
    int l = 0, r = -1, t = 0;
    for (auto &q : queries) {
      while(t < q.t) update(l,r,t++);
      while(t > q.t) update(l,r,--t);
      while(l > q.l) add(--l);
      while(r < q.r) add(++r);
      while(l < q.l) remove(l++);
      while(r > q.r) remove(r--);
      ans[q.id] = get_ans();
    }
    return ans;
  }

  // customize depending on problem
  int ans = 0;

  void init(){
    // initialize custom stuff
  }
  void remove(int i) {
    // remove a[i] from the current ans
  }
  void add(int i) {
    // add a[i] to the current ans
  }
  int get_ans() {}
};
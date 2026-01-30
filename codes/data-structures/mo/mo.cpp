struct Mo {
  struct Query {
    int l, r, idx, b;
    bool operator<(const Query& o) const {
      return b != o.b ? b < o.b : 
        (b & 1 ? r > o.r : r < o.r);
    }
  };

  int n, block_sz;

  // custom stuff
  vi freq, a;
  int ans = 0;

  vector<Query> queries;
  Mo(int n) : n(n), block_sz(round(sqrt(n))) {}

  // [l,r] indexed
  void add_query(int l, int r, int i) {
    queries.push_back({l,r,i,l/block_sz});
  }
  void add(int i) {
    // add val at i
    freq[a[i]]++;
    if (freq[a[i]] == 1) ans++;
  }
  void remove(int i) {
    // remove value at i
    freq[a[i]]--;
    if (freq[a[i]] == 0) ans--;
  }
  int get_ans() {
    // compute current answer
    return ans;
  }

  vi run() {
    vi ans(queries.size());
    sort(queries.begin(), queries.end());
    int l = 0, r = -1;
    for (auto& q : queries) {
      while (l > q.l) add(--l);
      while (r < q.r) add(++r);
      while (l < q.l) remove(l++);
      while (r > q.r) remove(r--);
      ans[q.idx] = get_ans();
    }
    return ans;
  }
};
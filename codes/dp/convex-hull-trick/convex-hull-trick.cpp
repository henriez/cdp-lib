struct CHT {
  struct Line { // y = mx + c
    int m, c;
    Line(int m, int c) : m(m), c(c) {}
    int val(int x){
      return m*x + c;
    }
    int floorDiv(int num, int den) {
      if (den < 0) num = -num, den = -den;
      if (num >= 0) return num / den;
      else return - ( (-num + den - 1) / den );
    }
    int ceilDiv(int num, int den) {
      if (den < 0) num = -num, den = -den;
      if (num >= 0) return (num + den - 1) / den;
      else return - ( (-num) / den );
    }
    int intersect(Line l){
      // m1x + c1 = m2x + c2
      // x = (c2 - c1)/(m1 - m2)
      // if slopes are increasing, use floor div
      return ceilDiv(l.c - c, m - l.m);
    }
  };

  deque<pair<Line, int>> dq;

  void insert(int m, int c){
    Line newLine(m, c);
    if (!dq.empty() && newLine.m == dq.back().first.m) {
      // If slopes increasing, change to <=
      if (newLine.c >= dq.back().first.c) return;
      else dq.pop_back();
    }
    // if slopes increasing, change to <=
    while (dq.size() > 1 && dq.back().second >= dq.back().first.intersect(newLine)){
      dq.pop_back();
    }
    if (dq.empty()){
      // assuming queries are positive numbers, may change to -INF or +INF if needed
      dq.emplace_back(newLine, 0);
      return;
    }
    dq.emplace_back(newLine, dq.back().first.intersect(newLine));
  }

  // dont use query and queryNonMonotonicValues in the same problem
  int query(int x){
    while (dq.size() > 1){
      // if slopes increasing, change to >=
      if (dq[1].second <= x) dq.pop_front();
      else break;
    }
    return dq[0].first.val(x);
  }


  int queryNonMonotonicValues(int x){
    int l=0, r=dq.size()-1, ans=0;
    while (l <= r) {
      int mid = (l+r)>>1;
      if (dq[mid].second <= x) {
        ans = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return dq[ans].first.val(x);
  }
};

void solve(){
  int n, c; cin >> n >> c;
  vi h(n);
  for (auto &x : h) cin >> x;

  vi dp(n);
  dp[0] = 0;
  CHT cht;
  cht.insert(-2*h[0], h[0]*h[0]);
  for (int i = 1; i < n; i++){
    dp[i] = cht.query(h[i]) + c + h[i]*h[i];
    cht.insert(-2*h[i], h[i]*h[i] + dp[i]);
  }
  cout << dp[n-1] << endl;
}

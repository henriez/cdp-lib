#define ALPHABET 26
struct SAM {
  struct State {
    int len = 0, link = -1;
    int cnt = 0, first_occ = -1;
    int next[ALPHABET];
    State() { fill(next, next + ALPHABET, -1); }
  };
  vector<State> st;
  int last;
  SAM(const string &s) {
    st.reserve(2*s.length());
    st.push_back(State());
    last = 0;
    for (int i = 0; i < s.size(); i++) extend(s[i],i);
    calc_cnt();
  }
  void extend(char c, int id) {
    int cur = st.size();
    st.push_back(State());
    st[cur].len = st[last].len + 1;
    st[cur].first_occ = id;
    st[cur].cnt = 1; 
    int p = last;
    while (p != -1 && st[p].next[c-'a'] == -1) {
      st[p].next[c-'a'] = cur;
      p = st[p].link;
    }
    if (p == -1) {
      st[cur].link = 0; 
      last = cur;
      return;
    }
    int q = st[p].next[c - 'a'];
    if (st[p].len + 1 == st[q].len) {
      st[cur].link = q;
      last = cur;
      return;
    }
    int clone = st.size();
    st.push_back(st[q]); 
    st[clone].len = st[p].len + 1;
    st[clone].cnt = 0;
    while (p != -1 && st[p].next[c - 'a'] == q) {
      st[p].next[c - 'a'] = clone;
      p = st[p].link;
    }
    st[q].link = st[cur].link = clone;
    last = cur;
  }
  void calc_cnt() {
    int sz = st.size();
    int mx = 0;
    for (auto &s : st) mx = max(mx, s.len);
    vi c(mx+1);
    vi nodes(sz);
    for (int i = 0; i < sz; i++) c[st[i].len]++;
    for (int i = 1; i <= mx; i++) c[i] += c[i-1];
    for (int i = 0; i < sz; i++) nodes[--c[st[i].len]] = i;
    for (int i = sz-1; i >= 0; i--) {
      int u = nodes[i];
      if (st[u].link != -1) st[st[u].link].cnt += st[u].cnt;
    }
  }
  string longest_common_substring(const string &t) {
    int v = 0, l = 0, len = 0, pos = 0;
    for (int i = 0; i < t.length(); i++) {
      int c = t[i] - 'a';
      while (v != 0 && st[v].next[c] == -1) {
        v = st[v].link;
        l = st[v].len;
      }
      if (st[v].next[c] != -1) {
        v = st[v].next[c];
        l++;
      }
      if (l > len) {
        len = l;
        pos = i;
      }
    }
    if (len == 0) return "";
    return t.substr(pos-len+1, len);
  }
  int count_occurrences(const string &t){
    int cur = 0;
    for (char c : t){
      if (st[cur].next[c-'a'] == -1) return 0;
      cur = st[cur].next[c-'a'];
    }
    return st[cur].cnt;
  }
  int first_occurrence(const string &t){
    int cur = 0;
    for (char c : t){
      if (st[cur].next[c-'a'] == -1) return -1;
      cur = st[cur].next[c-'a'];
    }
    return st[cur].first_occ-t.length()+1;
  }
  ll distinct_substrings(){
    ll ans = 0;
    for (int i = 1; i < st.size(); i++)
      ans += st[i].len - st[st[i].link].len;
    return ans;
  }
  vector<ll> distinct_substrings_perlen(int n){
    vector<ll> diff(n+2);
    for (int i = 1; i < st.size(); i++){
      int l = st[st[i].link].len+1;
      int r = st[i].len;
      diff[l]++; diff[r+1]--;
    }
    vector<ll> ans(n+1);
    ans[0] = diff[0];
    for (int i = 1; i <= n; i++){
      ans[i] = ans[i-1]+diff[i];
    }
    return ans;
  }
  vector<ll> dp;
  void calc_paths(int u){
    if (dp[u] != -1) return;
    dp[u]=1;
    for (int c = 0; c < ALPHABET; c++){
      int v = st[u].next[c];
      if (v == -1) continue;
      calc_paths(v);
      dp[u] += dp[v];
    }
  }
  string find_kth(ll k) {
    dp.assign(st.size(), -1);
    calc_paths(0);
    int u = 0;
    string ans = "";
    while (k > 0) {
      for (int c = 0; c < ALPHABET; c++) {
        int v = st[u].next[c];
        if (v == -1) continue;
        if (k <= dp[v]) {
          ans += 'a' + c;
          u = v;
          k--;
          break;
        } else k -= dp[v];
      }
    }
    return ans;
  }
  void calc_paths_with_repetitions(int u){
    if (dp[u] != -1) return;
    dp[u]=st[u].cnt;
    for (int c = 0; c < ALPHABET; c++){
      int v = st[u].next[c];
      if (v==-1) continue;
      calc_paths_with_repetitions(v);
      dp[u] += dp[v];
    }
  }
  string find_kth_with_repetitions(ll k){
    dp.assign(st.size(),-1);
    calc_paths_with_repetitions(0);
    int u = 0;
    string ans = "";
    while(k>0){
      for (int c = 0; c < ALPHABET; c++){
        int v = st[u].next[c];
        if (v==-1) continue;
        if (k <= dp[v]) {
          ans += 'a' + c;
          u = v;
          k -= st[v].cnt;
          break;
        } else k -= dp[v];
      }
    }
    return ans;
  }
};
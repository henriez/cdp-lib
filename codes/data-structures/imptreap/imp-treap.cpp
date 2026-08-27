mt19937 rng(1337); // change to chrono
struct implicit_treap {
  struct tag {
    int add = 0;
    bool has = false;
  };
  struct node {
    node *l = 0, *r = 0;
    uint32_t y = rng();
    int sz = 1;
    bool rev = false;
    // custom data
    int val = 0, sum = 0;
    tag lazy;
    
    node(int _val) : val(_val), sum(_val) {}
    void apply(tag t) {
      if (!t.has) return;
      val += t.add;
      sum += t.add * sz;
      lazy.add += t.add;
      lazy.has = true;
    }
    void push() {
      if (rev) {
        swap(l, r);
        if (l) l->rev ^= 1;
        if (r) r->rev ^= 1;
        rev = false;
      }
      if (lazy.has) {
        if (l) l->apply(lazy);
        if (r) r->apply(lazy);
        lazy = tag();
      }
    }
    void pull() {
      sz = 1;
      sum = val;
      if (l) { sz += l->sz; sum += l->sum; }
      if (r) { sz += r->sz; sum += r->sum; }
    }
  };
  node* root = 0;
  inline int size(node* t) { return t ? t->sz : 0; }
  // split node t's first k indices
  // write output treaps into L and R
  void split(node* t, int k, node*& L, node*& R) {
    if (!t) { L = R = 0; return; }
    t->push();
    if (size(t->l) >= k) {
      split(t->l, k, L, t->l);
      R = t;
    } else {
      split(t->r, k - size(t->l) - 1, t->r, R);
      L = t;
    }
    t->pull();
  }
  // merge nodes L and R and write it into t
  void merge(node*& t, node* L, node* R) {
    if (!L || !R) { t = L ? L : R; return; }
    L->push(); R->push();
    if (L->y > R->y) {
      merge(L->r, L->r, R);
      t = L;
    } else {
      merge(R->l, L, R->l);
      t = R;
    }
    t->pull();
  }
  implicit_treap(const vi& a) { // O(N) build
    vector<node*> st; st.reserve(a.size());
    for (int x : a) {
      node *cur = new node(x), *last = 0;
      while (!st.empty() && st.back()->y < cur->y) {
        last = st.back(); st.pop_back();
      }
      cur->l = last;
      if (!st.empty()) st.back()->r = cur;
      st.push_back(cur);
    }
    root = st.empty() ? nullptr : st.front();
    auto dfs = [&](auto &&dfs, node *t) -> void {
      if (!t) return;
      dfs(dfs,t->l);
      dfs(dfs,t->r);
      t->pull();
    }; dfs(dfs,root);
  }
  void insert(int pos, int val) {
    node *L, *R;
    split(root, pos, L, R);
    merge(L, L, new node(val));
    merge(root, L, R);
  }
  void remove(int pos) {
    node *L, *mid, *R;
    split(root, pos, L, R);
    split(R, 1, mid, R);
    delete mid;
    merge(root, L, R);
  }
  void rangeUpdate(int l, int r, tag v) {
    node *L, *mid, *R;
    split(root, l, L, R);
    split(R, r - l + 1, mid, R);
    if (mid) mid->apply(v);
    merge(R, mid, R);
    merge(root, L, R);
  }
  void reverse(int l, int r) {
    node *L, *mid, *R;
    split(root, l, L, R);
    split(R, r - l + 1, mid, R);
    if (mid) mid->rev ^= 1;
    merge(R, mid, R);
    merge(root, L, R);
  }
  int query(int l, int r) {
    node *L, *mid, *R;
    split(root, l, L, R);
    split(R, r - l + 1, mid, R);
    int ans = mid ? mid->sum : 0;
    merge(R, mid, R);
    merge(root, L, R);
    return ans;
  }
  vi output(){ // full array output
    vi ans; ans.reserve(size(root));
    auto go = [&](auto &&go, node *t) -> void {
      if (!t) return;
      t->push();
      go(go,t->l);
      ans.push_back(t->val);
      go(go,t->r);
    }; go(go,root);
    return ans;
  }
  void erase_range(int l, int r) {
    node *L, *mid, *R;
    split(root, l, L, R);
    split(R, r - l + 1, mid, R);
    // care for mem leaks, destroy mid recursively if needed
    merge(root, L, R);
  }
  void insert_range(int pos, node* new_treap) {
    node *L, *R;
    split(root, pos, L, R);
    merge(L, L, new_treap);
    merge(root, L, R);
  }
};
namespace DoubleHashing {
  const int MOD1 = 2147483647, MOD2 = 2147483629;
  using mint1 = mint<MOD1>;
  using mint2 = mint<MOD2>;
  vector<mint1> pmod1{1}, invpmod1{1};
  vector<mint2> pmod2{1}, invpmod2{1};

  const int MAX_VAL = 256;
  const int OFFSET = 'a'-1;
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  const mint1 p1 = uniform_int_distribution<int>(MAX_VAL+1, MOD1-1)(rng);
  const mint2 p2 = uniform_int_distribution<int>(MAX_VAL+1, MOD2-1)(rng);
  const mint1 inv1 = mint1::inv(p1);
  const mint2 inv2 = mint2::inv(p2);

  void extend(int n){
    while(pmod1.size() <= n){
      pmod1.push_back(pmod1.back()*p1);
      pmod2.push_back(pmod2.back()*p2);
      invpmod1.push_back(invpmod1.back()*inv1);
      invpmod2.push_back(invpmod2.back()*inv2);
    }
  }
  struct Hash {
    mint1 h1;
    mint2 h2;
    int len = 0;
    Hash apply(int x) const {
      extend(len+1);
      return {
        h1+pmod1[len]*(x-OFFSET),
        h2+pmod2[len]*(x-OFFSET),
        len+1
      };
    }
    bool operator<(const Hash &o) const {
      if (h1.val != o.h1.val) return h1.val < o.h1.val;
      if (h2.val != o.h2.val) return h2.val < o.h2.val;
      return len < o.len;
    }
    bool operator==(const Hash &o) const {
      return h1.val == o.h1.val && h2.val == o.h2.val && len == o.len;
    }
  };

  struct PrefixHash {
    vector<Hash> pref;
    PrefixHash(const string &s){
      int n = s.length();
      pref.reserve(n+1);
      pref.emplace_back();
      for (auto c : s) 
        pref.push_back(pref.back().apply(c));
    }
    Hash get(int l, int r) const {
      l++,r++;
      mint1 h1 = (pref[r].h1 - pref[l-1].h1)*invpmod1[l-1];
      mint2 h2 = (pref[r].h2 - pref[l-1].h2)*invpmod2[l-1];
      return {h1,h2,r-l+1};
    }
  };
};
template<const int MOD>
struct mint {
  int val;
  mint(ll v=0){
    ll x = v%MOD;
    if (x<0) x+=MOD;
    val = x;
  }
  mint& operator+=(const mint &o){
    ll x = (ll)val + o.val;
    if (x >= MOD) x -= MOD;
    val = x;
    return *this;
  }
  mint& operator-=(const mint &o){
    ll x = (ll)val - o.val;
    if (x < 0) x += MOD;
    val = x;
    return *this;
  }
  mint& operator*=(const mint &o){
    val = (1ll*val*o.val)%MOD;
    return *this;
  }
  mint& operator/=(const mint &o){
    val = (1ll*val*inv(o).val)%MOD;
    return *this;
  }
  friend mint operator+(mint a, const mint &b) { return a+=b; }
  friend mint operator-(mint a, const mint &b) { return a-=b; }
  friend mint operator*(mint a, const mint &b) { return a*=b; }
  friend mint operator/(mint a, const mint &b) { return a/=b; }
  static mint power(mint b, int e){
    mint ans = 1;
    while(e>0){
      if (e&1) ans *= b;
      b*=b; e>>=1;
    }
    return ans;
  }
  static mint inv(mint n){ return power(n,MOD-2); }
};
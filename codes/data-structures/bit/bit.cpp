// [l,r] interval convention and 0-indexed parameters
struct BIT {
  vector<int> bit;
  int n;
  BIT(int _n = 0){
    n = _n;
    bit.assign(n+1,0);
  }
  int presum(int i){
    int ans = 0;
    for (++i; i > 0; i -= i&-i) 
      ans += bit[i];
    return ans;
  }
  int sum(int l, int r){
    return presum(r) - presum(l-1);
  }
  void add(int i, int v){
    for (++i; i <= n; i += i&-i) 
      bit[i] += v;
  }
};

struct RangeBIT {
  BIT b1, b2;
  int n;
  RangeBIT(int _n){
    n = _n;
    b1 = b2 = BIT(n+2);
  }
  void add(int l, int r, int v){
    b1.add(l,v); 
    b1.add(r+1,-v);
    b2.add(l,v*(l-1)); 
    b2.add(r+1,-v*r);
  }
  int presum(int i){
    return b1.presum(i)*i - b2.presum(i);
  }
  int sum(int l, int r){
    return presum(r) - presum(l-1);
  }
};

int legendre(int n, int p){
  int ans = 0;
  while(n>0){
    n /= p; ans += n;
  }
  return ans;
}

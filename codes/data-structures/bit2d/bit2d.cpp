#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MAX 1123

int bit[MAX][MAX], x, y;
void setbit(int i, int j, int delta) {
  int j_;
  while(i <= x) {
    j_ = j;
    while(j_ <= y) {
      bit[i][j_] += delta;
      j_ += j_ & -j_;
    }
    i += i & -i;
  }
}
ll getbit(int i, int j) {
  ll ans = 0;
  int j_;
  while(i) {
    j_ = j;
    while(j_) {
      ans += bit[i][j_];
      j_ -= j_ & -j_;
    }
    i -= i & -i;
  }
  return ans;
}

int main(void) {
  int p;
  while (scanf("%d %d %d", &x, &y, &p), x || y || p) {
    for(int i = 0 ; i <=  x; i++)
      for(int j = 0; j <= y; j++)
        bit[i][j] = 0;
    int q;
    scanf("%d", &q);
    while(q--) {
      char c;
      scanf(" %c",&c);
      int n, xi, yi, zi, wi;
      if(c == 'A') {
        scanf(" %d %d %d", &n, &xi, &yi);
        xi++; yi++;
        setbit(xi, yi, n);
      }
      else {
        scanf(" %d %d %d %d", &xi, &yi, &zi, &wi);
        xi++; yi++; zi++; wi++;
        if(xi > zi) swap(xi, zi);
        if(yi > wi) swap(yi, wi);
        ll ans = getbit(zi, wi) - getbit(zi, yi - 1) 
        - getbit(xi - 1, wi) + getbit(xi - 1, yi - 1);
        printf("%lld\n", ans * (ll) p);
      }
    }
    printf("\n");
  }
  return 0;
}
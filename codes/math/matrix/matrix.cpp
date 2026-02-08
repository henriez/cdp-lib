template<typename T>
struct mat{
  vector<T> m;
  int n;

  mat(int _n = 0, bool identity = false) : n(_n) {
    m.resize(n*n);
    if (!identity) return;
    for (int i = 0; i < n; i++)
      m[i*n+i] = 1;
  }

  mat& operator+=(const mat &o){
    for (int i = 0; i < n; i++){
      int ra = i*n;
      for (int j = 0; j < n; j++){
        m[ra+j] += o.m[ra+j];
      }
    }
    return *this;
  }
  mat& operator-=(const mat& o){
    for (int i = 0; i < n; i++){
      int ra = i*n;
      for (int j = 0; j < n; j++){
        m[ra+j] -= o.m[ra+j];
      }
    }
    return *this;
  }
  mat& operator*=(const mat& o){
    vector<T> ans(n*n);
    for (int i = 0; i < n; i++){
      for (int k = 0; k < n; k++){
        int ra = i*n, rb = k*n;
        for (int j = 0; j < n; j++){
          ans[ra+j] += m[ra+k] * o.m[rb+j];
        }
      }
    }
    this->m = ans;
    return *this;
  }
  friend mat operator+(mat a, const mat& b){
    return a+=b;
  }
  friend mat operator-(mat a, const mat& b){
    return a-=b;
  }
  friend mat operator*(mat a, const mat& b){
    return a*=b;
  }
  T* operator[](int i){
    return &m[i*n];
  }
  vector<T> operator*(const vector<T> &v){
    vector<T> ans(n);
    for (int i = 0; i < n; i++){
      int ra = i*n;
      for (int j = 0; j < n; j++)
        ans[i] += m[ra+j]*v[j];
    }
    return ans;
  }
  mat operator^(int e){
    return exp(*this, e);
  }
  static mat exp(mat b, int e){
    mat ans = mat(b.n,true);
    while(e>0){
      if(e&1) ans*=b;
      b*=b;
      e>>=1;
    }
    return ans;
  }
};
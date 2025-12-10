void fft(vector<cd> &a, bool invert){
  int len = a.size();
  for(int i = 1, j = 0; i < len; i++){
    int bit = len >> 1;
    while(bit & j){
      j ^= bit;
      bit >>= 1;
    }
    j ^= bit;
    if(i < j) swap(a[i], a[j]);
  }
  for(int l = 2; l <= len; l <<= 1){
    double ang = 2*PI/l * (invert ? -1: 1);
    cd wd(cos(ang), sin(ang));
    for(int i = 0; i < len; i += l){
      cd w(1);
      for(int j = 0; j < l/2; j++){
        cd u = a[i+j], v = a[i+j+l/2];
        a[i+j] = u+w*v;
        a[i+j+l/2] = u-w*v;
        w *= wd;
      }
    }
  }
  if(invert){
    for(int i = 0; i < len; i++){
      a[i] /= len;
    }
  }
}
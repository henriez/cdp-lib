// odd[i] - max half length of odd palindromes centered in [i]
// even[i] - max half length of even palindromes centered in [i] (right part)
// ex:   a b a b b a c a
// odd:  1 2 2 1 1 1 2 1
// even: 0 0 0 0 2 0 0 0
struct Manacher {
  vi odd, even;
  int count = 0;
  Manacher (const string &s) {
    int n = s.size();
    odd = even = vi(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
      int k = i > r ? 1 : min(odd[l+r-i], r-i+1);
      while (i-k >= 0 && i+k < n && s[i-k] == s[i+k]) k++;
      odd[i] = k;
      if (i+k-1 > r) l = i-k+1, r = i+k-1;
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
      int k = i > r ? 0 : min(even[l+r-i+1], r-i+1);
      while (i-k-1 >= 0 && i+k < n && s[i-k-1] == s[i+k]) k++;
      even[i] = k;
      if (i+k-1 > r) l = i-k, r = i+k-1;
    }
    count = 0;
    for (int i = 0; i < n; i++) count += odd[i]+even[i];
  }
  // query if substring s[l..r] is a palindrome
  bool is_palindrome(int l, int r) {
    int len = r-l+1, center = l+len/2;
    if (len&1) return odd[center] > len/2;
    return even[center] >= len/2;
  }
};

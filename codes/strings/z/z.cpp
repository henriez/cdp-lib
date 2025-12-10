vi compute_z(const string &s) {
    int n = s.length();
    vi z(n);
    int l = 0, r = 0;

    for (int i = 1; i < n; i++) {
        if (i <= r) 
            z[i] = min(r - i + 1, z[i-l]);
        
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

vi find_occurrences(const string &txt, const string &pat){
    vi occurences;
    vi z = compute_z(pat + '#' + txt);
    int n = txt.length(), m = pat.length();
    for (int i = 0; i < n+m+1; i++){
        if (z[i] == m) occurences.push_back(i-m-1);
    }
    return occurences;
}

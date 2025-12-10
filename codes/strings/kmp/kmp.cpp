vi compute_lps(const string &pat){
    int m = pat.length();
    vi lps(m);
    int len = 0;
    for (int i = 1; i < m; i++){
        while(len > 0 && pat[i] != pat[len]) 
            len = lps[len-1];
        if (pat[i] == pat[len]) len++;
        lps[i] = len;
    }
    return lps;
}

// find all occurrences
vi kmp_search(const string &txt, const string &pat){
    int n = txt.length();
    int m = pat.length();
    if (m == 0) return {};
    vi lps = compute_lps(pat);
    vi occurrences;
    int j = 0;
    for (int i = 0; i < n; i++){
        while (j > 0 && txt[i] != pat[j]) 
            j = lps[j-1];
        if (txt[i] == pat[j]) j++;

        if (j == m) {
            occurrences.push_back(i-m+1);
            j = lps[j-1];
        }
    }
    return occurrences;
}

// find all occurrences (simpler version)
vi kmp_search(const string &txt, const string &pat){
    int n = txt.length(), m = pat.length();
    vi lps = compute_lps(pat + '#' + txt);
    vi occurrences;
    for (int i = 0; i < n+m+1; i++){
        if (lps[i] == pat.length())
            occurrences.push_back(i-m*2);
    }
    return occurrences;
}

// borda sao os prefixos que tambem sao sufixos
vi find_borders(const string &s){
    vi lps = compute_lps(s);
    int i = s.length()-1;

    vi ans;
    while (lps[i] > 0){
        ans.push_back(lps[i]);
        i = lps[i]-1;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
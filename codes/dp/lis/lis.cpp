int lis(vi &a){
    int n = a.size();
    vi len(n+1, INF);
    len[0] = -INF;
    for (int i = 0; i < n; i++){
        int l = upper_bound(len.begin(), len.end(), a[i]) - len.begin();
        if(len[l-1] < a[i] && a[i] < len[l]) len[l] = a[i];
    }    

    int ans = 0;
    for (int i = 0; i <= n; i++){
        if (len[i] < INF) ans = i;
    }
    return ans;
}
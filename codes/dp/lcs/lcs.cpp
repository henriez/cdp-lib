vvi dp(n+1,vi(m+1));
vvii p(n+1,vii(m+1));

for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
        if (a[i-1] == b[j-1]) {
            dp[i][j] = dp[i-1][j-1]+1;
            p[i][j] = {i-1,j-1};
        } else if (dp[i][j-1] > dp[i-1][j]){
            dp[i][j] = dp[i][j-1];
            p[i][j] = {i,j-1};
        } else {
            dp[i][j] = dp[i-1][j];
            p[i][j] = {i-1,j};
        }
    }
}

ii pos = ii(n,m);
stack<int> st;
while(pos != ii(0,0)){
    auto [i,j] = pos;
    if (p[i][j] == ii(i-1,j-1)) st.push(a[i-1]);
    pos = p[i][j];
}
cout << st.size() << endl;
while (!st.empty()) {
    cout << st.top() << ' ';
    st.pop();
}
cout << endl;
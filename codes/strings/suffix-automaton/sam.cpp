struct SAM {
    struct State {
        int len,link;
        ll cnt = 0;
        int first_occ=-1;
        map<char,int> next;
    };

    vector<State> st;
    int last;

    SAM(string s){
        st.push_back({0,-1,0,-1});
        last = 0;
        for (int i = 0; i < s.length(); i++){
            extend(s[i],i);
        }
        calc_cnt();
    }

    void extend(char c, int id){
        int cur = st.size();
        st.push_back({st[last].len+1,0,1,id});
        int p = last;
        while(p!=-1 && st[p].next.count(c)==0){
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1){
            st[cur].link = 0;
            last = cur;
            return;
        } 

        int q = st[p].next[c];
        if (st[p].len+1 == st[q].len) {
            st[cur].link = q;
            last = cur;
            return;
        } 
        int clone = st.size();
        st.push_back({
            st[p].len+1,
            st[q].link,
            0,
            st[q].first_occ,
            st[q].next
        });
        while (p!=-1 && st[p].next[c] == q){
            st[p].next[c] = clone;
            p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
        last = cur;
    }

    void calc_cnt(){
        vi nodes(st.size());
        iota(nodes.begin(),nodes.end(),0);
        sort(nodes.begin(),nodes.end(),[&](int a, int b){
            return st[a].len > st[b].len;
        });

        for (int u : nodes){
            if (st[u].link != -1){
                st[st[u].link].cnt += st[u].cnt;
            }
        }
    }

    int count_occurrences(string t){
        int cur = 0;
        for (char c : t){
            if (st[cur].next.count(c) == 0) return 0;
            cur = st[cur].next[c];
        }
        return st[cur].cnt;
    }

    int first_occurrence(string t){
        int cur = 0;
        for (char c : t){
            if (!st[cur].next.count(c)) return -2;
            cur = st[cur].next[c];
        }
        return st[cur].first_occ-t.length()+1;
    }

    int distinct_substrings(){
        int ans = 0;
        for (int i = 1; i < st.size(); i++)
            ans += st[i].len - st[st[i].link].len;
        return ans;
    }

    vi distinct_substrings_perlen(int n){
        vi diff(n+2);
        for (int i = 1; i < st.size(); i++){
            int l = st[st[i].link].len+1;
            int r = st[i].len;
            diff[l]++; diff[r+1]--;
        }
        vi ans(n+1);
        ans[0] = diff[0];
        for (int i = 1; i <= n; i++){
            ans[i] = ans[i-1]+diff[i];
        }

        return ans;
    }

    vi dp;
    void calc_paths(int u){
        if (dp[u] != -1) return;
        dp[u]=1;
        for (auto [c,v] : st[u].next){
            calc_paths(v);
            dp[u] += dp[v];
        }
    }

    string find_kth(int k){
        dp.assign(st.size(),-1);
        calc_paths(0);
        int u = 0;
        string ans = "";
        while(k>0){
            for (auto [c,v] : st[u].next){
                bool ok = false;
                if (k <= dp[v]){
                    ans += c;
                    u = v;
                    k--;
                    ok = true;
                    break;
                }
                if (!ok) k-=dp[v];
            }
        }
        return ans;
    }

        void calc_paths_with_repetitions(int u){
        if (dp[u] != -1) return;
        dp[u]=st[u].cnt;
        for (auto [c,v] : st[u].next){
            calc_paths_with_repetitions(v);
            dp[u] += dp[v];
        }
    }

    string find_kth_with_repetitions(int k){
        dp.assign(st.size(),-1);
        calc_paths_with_repetitions(0);
        int u = 0;
        string ans = "";
        while(k>0){
            for (auto [c,v] : st[u].next){
                bool ok = false;
                if (k <= dp[v]){
                    ans += c;
                    k-=st[v].cnt;
                    u = v;
                    ok = true;
                    break;
                }
                if (!ok) k-=dp[v];
            }
        }
        return ans;
    }
};
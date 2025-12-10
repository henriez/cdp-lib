class Hashing{
    const int mod0 = 1e9+7;
    vi pmod0;
    vull pmod1;

    public:
    void CalcP(int mn, int n){
        random_device rd;
        uniform_int_distribution<int> dist(mn+2, mod0-1);
        int p = dist(rd);
        if(p % 2 == 0) p--;
        pmod0 = vi(n);
        pmod1 = vull(n);
        pmod0[0] = pmod1[0] = 1;
        for(int i = 1; i < n; i++){
            pmod0[i] = (pmod0[i-1] * p) % mod0;
            pmod1[i] = (pmod1[i-1] * p);
        }
    }

    viull DistincSubstrHashes(string base, int offsetVal){
        int n = base.size();
        viull ans;
        for(int i = 0; i < n; i++){
            int h0 = 0;
            ull h1 = 0;
            for(int j = i; j < n; j++){
                h0 = (h0 + (base[j]-offsetVal)*pmod0[j-i]) % mod0;
                h1 = (h1 + (base[j]-offsetVal)*pmod1[j-i]);
                ans.push_back(iull(h0, h1));
            }
        }
        sort(ans.begin(), ans.end());
        auto last = unique(ans.begin(), ans.end());
        ans.erase(last, ans.end());
        return ans;
    };

    viull WindowHash(string data, int offsetVal, int lenWindow){
        int n = data.size();
        int h0 = 0;
        ull h1 = 0;
        viull ans;
        for(int i = 0; i < lenWindow; i++){
            h0 = (h0 + (data[i]+offsetVal)*pmod0[i]) % mod0;
            h1 = (h1 + (data[i]+offsetVal)*pmod1[i]);
        }
        ans.push_back(iull((h0*pmod0[n-1])%mod0, h1*pmod1[n-1]));
        for(int i = lenWindow; i < n; i++){
            h0 = (h0 - (data[i-lenWindow]+offsetVal)*pmod0[i-lenWindow]) % mod0;
            h0 = (h0 + mod0) % mod0;
            h0 = (h0 + (data[i]+offsetVal)*pmod0[i]) % mod0;
            h1 = (h1 - (data[i-lenWindow]+offsetVal)*pmod1[i-lenWindow]);
            h1 = (h1 + (data[i]+offsetVal)*pmod1[i]);
            ans.push_back(iull((h0*pmod0[n-1-(i-lenWindow+1)])%mod0, h1*pmod1[n-1-(i-lenWindow+1)]));
        }
        return ans;
    };
};
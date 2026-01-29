    template<typename T, ll MOD, ll ROOT>
    void transform(vector<T>& a, bool invert) {
        int n = a.size();

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            T wlen = T::power(ROOT, (MOD - 1) / len);
            if (invert) wlen = T::inv(wlen);
            for (int i = 0; i < n; i += len) {
                T w = 1;
                for (int j = 0; j < len / 2; j++) {
                    T u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            T n_inv = T::inv(n);
            for (T& x : a)
                x *= n_inv;
        }
    }

    template<typename T, ll MOD, ll ROOT>
    vector<ll> multiply(const vector<ll>& a, const vector<ll>& b) {
        vector<T> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < a.size() + b.size()) n <<= 1;
        fa.resize(n);
        fb.resize(n);

        transform<T, MOD, ROOT>(fa, false);
        transform<T, MOD, ROOT>(fb, false);

        for (int i = 0; i < n; i++) fa[i] *= fb[i];
        
        transform<T, MOD, ROOT>(fa, true);

        vector<ll> result(n);
        for (int i = 0; i < n; i++) result[i] = fa[i].val;
        return result;
    }
    
    vector<ll> crt_multiply(const vector<ll>& a, const vector<ll>& b) {
        const ll mod1 = 998244353;
        const ll root1 = 3;
        using mint1 = mint<mod1>;
        vector<ll> ans1 = NTT::multiply<mint1, mod1, root1>(a, b);
        
        const ll mod2 = 1004535809;
        const ll root2 = 3;
        using mint2 = mint<mod2>;
        vector<ll> ans2 = NTT::multiply<mint2, mod2, root2>(a, b);
        
        int ans_size = a.size() + b.size() - 2;
        ll M1_inv_M2 = mint<mod2>::inv(mod1).val;
        
        vector<ll> final_result(ans_size + 1);
        for (int i = 0; i <= ans_size; ++i) {
            ll v1 = ans1[i];
            ll v2 = ans2[i];
            ll k = ((v2 - v1 + mod2) % mod2 * M1_inv_M2) % mod2;
            final_result[i] = v1 + k * mod1;
        }
        return final_result;
    }
}
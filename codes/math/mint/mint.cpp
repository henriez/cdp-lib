template<ll MOD>
struct mint {
    ll val;
    mint(ll v = 0) { 
        if (v < 0) v = v % MOD + MOD; 
        if (v >= MOD) v %= MOD; 
        val = v; 
    }
    mint& operator+=(const mint& other) { 
        val += other.val; 
        if (val >= MOD) val -= MOD; 
        return *this; 
    }
    mint& operator-=(const mint& other) { 
        val -= other.val; 
        if (val < 0) val += MOD; 
        return *this; 
    }
    mint& operator*=(const mint& other) { 
        val = (val * other.val) % MOD; 
        return *this; 
    }
    mint& operator/=(const mint& other) { 
        val = (val * inv(other).val) % MOD; 
        return *this; 
    }
    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    static mint power(mint b, ll e) { 
        mint ans = 1; 
        while (e > 0) { 
            if (e & 1) ans *= b; 
            b *= b; 
            e /= 2; 
        } 
        return ans; 
    }
    static mint inv(mint n) { return power(n, MOD - 2); }
};
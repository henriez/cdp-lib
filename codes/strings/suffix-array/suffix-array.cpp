struct SuffixArray {
    int sz;
    vi suff_ind, lcp;
    viii suffs;

    void radix_sort() {
        if (sz <= 1) return;
        viii suffs_new(sz);
        vi cnt(sz + 1, 0); /*rever esse tamanho*/

        for (auto& item : suffs) cnt[item.first.second]++;
        for (int i = 1; i <= sz; ++i) cnt[i] += cnt[i - 1];
        for (int i = sz - 1; i >= 0; --i) suffs_new[--cnt[suffs[i].first.second]] = suffs[i];
        
        cnt.assign(sz + 1, 0);
        for (auto& item : suffs_new) cnt[item.first.first]++;
        for (int i = 1; i <= sz; ++i) cnt[i] += cnt[i - 1];
        for (int i = sz - 1; i >= 0; --i) suffs[--cnt[suffs_new[i].first.first]] = suffs_new[i];
    }

    void build_lcp(vi& a) {
        lcp.assign(sz, 0);
        vi rank(sz);
        for (int i = 0; i < sz; ++i) rank[suff_ind[i]] = i;

        int h = 0;
        for (int i = 0; i < sz; ++i) {
            if (rank[i] == sz - 1) { h = 0; continue; }
            if (h > 0) h--;
            int j = suff_ind[rank[i] + 1];
            while (i + h < sz && j + h < sz && a[i + h] == a[j + h]) h++;
            lcp[rank[i] + 1] = h;
        }
    }

    void build(vi& a) {
        a.push_back(0);
        sz = a.size();
        suffs.resize(sz);
        suff_ind.resize(sz);
        vi equiv(sz);


        for (int i = 0; i < sz; ++i) suffs[i] = iii(ii(a[i],a[i]), i);
        radix_sort();
        for (int i = 1; i < sz; ++i) {
            auto [c,ci] = suffs[i];
            auto [p,pi] = suffs[i-1];
            equiv[ci] = equiv[pi] + (c > p);
        }

        for (int suflen = 1; suflen < sz; suflen *= 2) {
            for (int i = 0; i < sz; ++i) {
                suffs[i] = {{equiv[i], equiv[(i + suflen) % sz]}, i};
            }
            radix_sort();
            for (int i = 1; i < sz; ++i) {
                auto [c,ci] = suffs[i];
                auto [p,pi] = suffs[i-1];
                equiv[ci] = equiv[pi] + (c > p);
            }
        }

        for(int i = 0; i < sz; ++i) suff_ind[i] = suffs[i].second;
        build_lcp(a);
        
        a.pop_back();
        sz--;
        suff_ind.erase(suff_ind.begin());
        lcp.erase(lcp.begin());
    }
};
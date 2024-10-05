class quick_union {
public:
    size_t n;
    vector<size_t> c, sz;
    vector<pair<size_t, size_t>> history;
public:
    quick_union(size_t n) : n(n), c(n), sz(n) {
        iota(c.begin(), c.end(), 0);
        sz.assign(n, 1);
    }

    size_t query(size_t i) {
        if (c[i] != i) return query(c[i]);
        return c[i];
    }

    void merge(size_t i, size_t j) {
        if (connected(i, j)) {
            history.emplace_back(n, n);
        } else {
            i = query(i), j = query(j);
            if (sz[i] > sz[j]) swap(i, j);
            history.emplace_back(i, j);
            sz[j] += sz[i];
            c[i] = j;
        }
    }

    bool connected(size_t i, size_t j) {
        return query(i) == query(j);
    }

    size_t query_size(size_t i) {
        return sz[query(i)];
    }

    void rollback() {
        auto [i, j] = popback(history);
        if (i == n and j == n) return;
        c[i] = i;
        sz[j] -= sz[i];
    }
};

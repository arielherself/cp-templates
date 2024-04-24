class quick_union {
private:
    vector<size_t> c, sz;
public:
    quick_union(size_t n) : c(n), sz(n) {
        iota(c.begin(), c.end(), 0);
        sz.assign(n, 1);
    }
    
    size_t query(size_t i) {
        if (c[i] != i) c[i] = query(c[i]);
        return c[i];
    }
    
    void merge(size_t i, size_t j) {
        sz[query(j)] += sz[query(i)];
        c[query(i)] = query(j);
    }

    bool connected(size_t i, size_t j) {
        return query(i) == query(j);
    }

    size_t query_size(size_t i) {
        return sz[query(i)];
    }
};

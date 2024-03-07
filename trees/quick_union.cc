class quick_union {
private:
    vector<size_t> c;
public:
    quick_union(size_t n) : c(n) {
        iota(c.begin(), c.end(), 0);
    }
    
    size_t query(size_t i) {
        if (c[i] != i) c[i] = query(c[i]);
        return c[i];
    }
    
    void merge(size_t i, size_t j) {
        c[query(i)] = query(j);
    }

    bool connected(size_t i, size_t j) {
        return query(i) == query(j);
    }
};


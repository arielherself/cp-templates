class quick_union {
private:
	vector<size_t> c, sz;
public:
	quick_union() = default;
	always_inline quick_union(size_t n) : c(n), sz(n) {
		iota(c.begin(), c.end(), 0);
		sz.assign(n, 1);
	}

	always_inline void resize(size_t n) {
		c.resize(n);
		iota(c.begin(), c.end(), 0);
		sz.assign(n, 1);
	}

	always_inline size_t query(size_t i) {
		while (i != c[i]) {
			i = c[i] = c[c[i]];
		}
		return i;
	}

	always_inline void merge(size_t i, size_t j) {
		if (connected(i, j)) return;
		sz[query(j)] += sz[query(i)];
		c[query(i)] = query(j);
	}

	always_inline bool connected(size_t i, size_t j) {
		return query(i) == query(j);
	}

	always_inline size_t query_size(size_t i) {
		return sz[query(i)];
	}
};

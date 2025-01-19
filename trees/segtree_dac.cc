template<typename Addable_Info_t, typename Tag_t, typename Sequence = std::vector<Addable_Info_t>> class segtree {
private:
	using size_type = uint64_t;
	using info_type = Addable_Info_t;
	using tag_type = Tag_t;
	size_type _max;
	vector<info_type> d;
	vector<tag_type> b;

	void range_apply(size_type s, size_type t, size_type p, size_type l, size_type r, const tag_type& c) {
		if (l <= s && t <= r) {
			d[p].apply(c, t - s + 1);
			return;
		}
		size_type m = s + (t - s >> 1);
		if (l <= m) range_apply(s, m, p * 2, l, r, c);
		if (r > m)	range_apply(m + 1, t, p * 2 + 1, l, r, c);
	}
	void range_query(size_type s, size_type t, size_type p, size_type l, size_type r) {
		int cnt = 0;
		for (auto&& [u, v] : d[p].ops) {
			qu.merge(u, v);
			++cnt;
		}
		if (s == t) {
			auto&& [v, idx] = queries[s];
			if (v != -1) {
				res[idx] = qu.query_size(v);
			}
		} else {
			size_type m = s + (t - s >> 1);
			if (l <= m) range_query(s, m, p * 2, l, r);
			if (r > m)	range_query(m + 1, t, p * 2 + 1, l, r);
		}
		while (cnt--) {
			qu.rollback();
		}
	}
public:
	segtree(size_type __max) : d(4 * __max), b(4 * __max), _max(__max - 1) {}

	void range_apply(size_type l, size_type r, const tag_type& c) {
		range_apply({}, _max, 1, l, r, c);
	}
	void range_query(size_type l, size_type r) {
		return range_query({}, _max, 1, l, r);
	}
	const vector<info_type>& get_d() {
		return d;
	}
};
struct Tag {
	int u = -1, v = -1;
	void apply(const Tag& rhs) {
	}
};
struct Info {
	vector<pii> ops;
	void apply(const Tag& rhs, size_t len) {
		if (rhs.u == -1 and rhs.v == -1) return;
		ops.emplace_back(rhs.u, rhs.v);
	}
};
Info operator+(const Info &a, const Info &b) {
	return {};
}

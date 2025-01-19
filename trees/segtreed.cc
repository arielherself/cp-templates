template<typename T> class segtreed {
private:
	using size_type = uint64_t;
	size_type cnt, root;
	T _max;
	vector<T> d, b;
	vector<size_type> ls, rs;

	void _update(size_type s, size_type t, size_type &p, size_type l, size_type r, T c) {
		if (!p) p = ++cnt;
		if (l <= s && t <= r) {
			d[p] += c * (t - s + 1);
			b[p] += c;
			return;
		}
		size_type m = s + (t - s >> 1);
		if (!ls[p]) ls[p] = ++cnt;
		if (!rs[p]) rs[p] = ++cnt;
		if (b[p] && s != t) {
			d[ls[p]] += b[p] * (m - s + 1), d[rs[p]] += b[p] * (t - m);
			b[ls[p]] += b[p], b[rs[p]] += b[p];
			b[p] = 0;
		}
		if (l <= m) _update(s, m, ls[p], l, r, c);
		if (r > m)	_update(m + 1, t, rs[p], l, r, c);
		d[p] = d[ls[p]] + d[rs[p]];
	}

	T _query(size_type s, size_type t, size_type p, size_type l, size_type r) {
		if (!p) return {};
		if (l <= s && t <= r) return d[p];
		size_type m = s + (t - s >> 1);
		T res = {};
		if (b[p]) {
			d[ls[p]] += b[p] * (m - s + 1), d[rs[p]] += b[p] * (t - m);
			b[ls[p]] += b[p], b[rs[p]] += b[p];
			b[p] = 0;
		}
		if (l <= m) res += _query(s, m, ls[p], l, r);
		if (r > m)	res += _query(m + 1, t, rs[p], l, r);
		return res;
	}
public:
	segtreed(size_type n, T _max) : cnt(0), root(0), d(4 * n, {}), b(4 * n, {}), ls(4 * n, 0), rs(4 * n, 0), _max(_max) {}

	void update(size_type l, size_type r, T c) {
		_update({}, _max, root, l, r, c);
	}

	T query(size_type l, size_type r) {
		return _query({}, _max, root, l, r);
	}
};

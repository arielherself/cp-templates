template<typename T> class segtree {
private:
	using size_type = uint64_t;
	T _max;
	vector<T> d, b;

	void _update(size_type s, size_type t, size_type p, size_type l, size_type r, T c) {
		if (l <= s && t <= r) {
			d[p] += c * (t - s + 1);
			b[p] += c;
			return;
		}
		size_type m = s + (t - s >> 1);
		if (b[p] && s != t) {
			d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
			b[p * 2] += b[p], b[p * 2 + 1] += b[p];
			b[p] = 0;
		}
		if (l <= m) _update(s, m, p * 2, l, r, c);
		if (r > m)	_update(m + 1, t, p * 2 + 1, l, r, c);
		d[p] = d[p * 2] + d[p * 2 + 1];
	}

	T _query(size_type s, size_type t, size_type p, size_type l, size_type r) {
		if (l <= s && t <= r) return d[p];
		size_type m = s + (t - s >> 1);
		T res = {};
		if (b[p]) {
			d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
			b[p * 2] += b[p], b[p * 2 + 1] += b[p];
			b[p] = 0;
		}
		if (l <= m) res += _query(s, m, p * 2, l, r);
		if (r > m)	res += _query(m + 1, t, p * 2 + 1, l, r);
		return res;
	}
public:
	segtree(T _max) : d(4 * _max, {}), b(4 * _max, {}), _max(_max) {}

	void update(size_type l, size_type r, T c) {
		_update({}, _max, 1, l, r, c);
	}

	T query(size_type l, size_type r) {
		return _query({}, _max, 1, l, r);
	}
};

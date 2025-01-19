template<typename T>
struct BIT2d {
	int n, m;
	vector<vector<T>> c;
	BIT2d(size_t n, size_t m) : n(n), m(m), c(n + 1, vector<T>(m + 1)) {}
	void add(size_t i, size_t j, const T& k) {
		while (i <= n) {
			size_t j1 = j;
			while (j1 <= m) {
				c[i][j1] += k;
				j1 += lowbit(j1);
			}
			i += lowbit(i);
		}
	}
	T getsum(size_t i, size_t j) {
		T res = {};
		while (i) {
			size_t j1 = j;
			while (j1) {
				res += c[i][j1];
				j1 -= lowbit(j1);
			}
			i -= lowbit(i);
		}
		return res;
	}
};

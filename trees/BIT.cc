template<typename T>
struct BIT {
	int n;
	vector<T> c;
	BIT(size_t n) : n(n), c(n + 1) {}
	void add(size_t i, const T& k) {
		while (i <= n) {
			c[i] += k;
			i += lowbit(i);
		}
	}
	T getsum(size_t i) {
		T res = {};
		while (i) {
			res += c[i];
			i -= lowbit(i);
		}
		return res;
	}
};

template <typename T>
vector<int> manacher(const vector<T>& s, const T& never) {
	vector<T> t = { never };
	for (auto&& c : s) {
		t.emplace_back(c);
		t.emplace_back(never);
	}
	int n = t.size();
	vector<int> r(n);
	for (int i = 0, j = 0; i < n; ++i) {
		if (2 * j - i >= 0 && j + r[j] > i) {
			r[i] = min(r[2 * j - i], j + r[j] - i);
		}
		while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]]) {
			r[i] += 1;
		}
		if (i + r[i] > j + r[j]) {
			j = i;
		}
	}
	for (int i = 0; i < n; i += 2) {
		r[i] = (r[i] - 1) / 2;
	}
	for (int i = 1; i < n; i += 2) {
		r[i] /= 2;
	}
	return r;
}

template <typename T>
struct basis {
	array<T, sizeof(T) * 8> p;
	int cnt = 0;

	basis(const vector<T>& v) {
		for (auto&& x : v) {
			insert(x);
		}
	}

	bool insert(T x) {
		for (size_t i = sizeof(T) * 8 - 1; ~i; --i) {
			if (not (x >> i)) continue;
			if (not p[i]) {
				p[i] = x;
				cnt += 1;
				return true;
			}
			x ^= p[i];
		}
		return false;
	}

	vector<T> value(void) const {
		vector<T> res;
		for (size_t i = sizeof(T) * 8 - 1; ~i; --i) {
			if (not p[i]) continue;
			res.emplace_back(p[i]);
		}
		return res;
	}
};


struct SA {
	int n;
	std::vector<int> sa, rk, lc;
	vector<vector<int>> st;

	SA(std::string s) {
		n = s.size();
		sa.resize(n);
		lc.resize(n - 1);
		rk.resize(n);
		std::iota(sa.begin(), sa.end(), 0);
		sort_by_key(sa.begin(), sa.end(), expr(s[i], int i));
		rk[sa[0]] = 0;
		for (int i = 1; i < n; i++) {
			rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
		}
		int k = 1;
		std::vector<int> tmp, cnt(n);
		tmp.reserve(n);
		while (rk[sa[n - 1]] < n - 1) {
			tmp.clear();
			for (int i = 0; i < k; i++) {
				tmp.push_back(n - k + i);
			}
			for (auto i : sa) {
				if (i >= k) {
					tmp.push_back(i - k);
				}
			}
			std::fill(cnt.begin(), cnt.end(), 0);
			for (int i = 0; i < n; i++) {
				cnt[rk[i]]++;
			}
			for (int i = 1; i < n; i++) {
				cnt[i] += cnt[i - 1];
			}
			for (int i = n - 1; i >= 0; i--) {
				sa[--cnt[rk[tmp[i]]]] = tmp[i];
			}
			std::swap(rk, tmp);
			rk[sa[0]] = 0;
			for (int i = 1; i < n; i++) {
				rk[sa[i]] = rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
			}
			k *= 2;
		}
		for (int i = 0, j = 0; i < n; i++) {
			if (rk[i] == 0) {
				j = 0;
			} else {
				for (j -= j > 0; i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j]; ) {
					j++;
				}
				lc[rk[i] - 1] = j;
			}
		}
		int m = lc.size();
		int lgm = m == 0 ? 0 : lg2(m);
		st = vector(lgm + 1, vector<int>(m));
		st[0] = lc;
		for (int j = 0; j < lgm; j++) {
			for (int i = 0; i + (2 << j) <= m; i++) {
				st[j + 1][i] = std::min(st[j][i], st[j][i + (1 << j)]);
			}
		}
	}

	int rmq(int l, int r) {
		int k = lg2(r - l);
		return std::min(st[k][l], st[k][r - (1 << k)]);
	}

	__attribute__((target("lzcnt")))
	int lcp(int i, int j) {
		if (i == j || i == n || j == n) {
			return std::min(n - i, n - j);
		}
		int a = rk[i];
		int b = rk[j];
		if (a > b) {
			std::swap(a, b);
		}
		return std::min({n - i, n - j, rmq(a, b)});
	}

	int lcs(int i, int j) {
		if (i == j || i == 0 || j == 0) {
			return std::min(i, j);
		}
		int a = rk[n + n - i];
		int b = rk[n + n - j];
		if (a > b) {
			std::swap(a, b);
		}
		return std::min({i, j, rmq(a, b)});
	}
};

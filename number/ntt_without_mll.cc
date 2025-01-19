template <ll M>
ll qpow_m(ll b, ll p) {
	if (b == 0 and p != 0) return 0;
	if (p == 0) return 1;
	ll half = qpow_m<M>(b, p / 2);
	if (p % 2 == 1) return (half * half % M)* b % M;
	else return half * half % M;
}


template <ll M>
void ntt(vector<ll>& y, bool idft) {
	int n = y.size();
	vector<int> rev(n);
	for (int i = 0; i < n; ++i) {
		rev[i] = rev[i >> 1] >> 1;
		if (i & 1) {
			rev[i] |= n >> 1;
		}
	}
	for (int i = 0; i < n; ++i) {
		if (i < rev[i]) {
			swap(y[i], y[rev[i]]);
		}
	}
	vector<ll> roots = { 0, 1 };
	if (roots.size() < n) {
		int k = lsp(roots.size());
		roots.resize(n);
		for (; (1 << k) < n; ++k) {
			ll e = qpow_m<M>(31, 1 << lsp(M - 1) - k - 1);
			for (int i = 1 << k - 1; i < (1 << k); ++i) {
				roots[2 * i] = roots[i];
				roots[2 * i + 1] = roots[i] * e % M;
			}
		}
	}
	for (int h = 2; h <= n; h <<= 1) {
		for (int j = 0; j < n; j += h) {
			for (int k = j; k < j + h / 2; ++k) {
				ll u = y[k], t = roots[k - j + h / 2] * y[k + h / 2] % M;
				y[k] = (u + t) % M;
				y[k + h / 2] = mod(u - t, M);
			}
		}
	}
	if (idft) {
		reverse(y.begin() + 1, y.end());
		ll inv = inverse(n, M);
		for (int i = 0; i < n; ++i) {
			y[i] = y[i] * inv % M;
		}
	}
}
template <ll M>
vector<ll> multiply(const vector<ll>& a, const vector<ll>& b) {
	vector<ll> A(a.begin(), a.end()), B(b.begin(), b.end());
	int n = 1;
	while (n < a.size() + b.size()) n <<= 1;
	A.resize(n), B.resize(n);
	ntt<M>(A, false), ntt<M>(B, false);
	for (int i = 0; i < n; ++i) {
		A[i] = A[i] * B[i] % M;
	}
	ntt<M>(A, true);
	return A;
}

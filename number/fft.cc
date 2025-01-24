void fft(vector<complex<ld>>& y, bool idft) {
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
	for (int h = 2; h <= n; h <<= 1) {
		complex<ld> wn(cos(2 * M_PI / h), sin(2 * M_PI / h));
		for (int j = 0; j < n; j += h) {
			complex<ld> w(1);
			for (int k = j; k < j + h / 2; ++k) {
				complex<ld> u = y[k], t = w * y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w *= wn;
			}
		}
	}
	if (idft) {
		reverse(y.begin() + 1, y.end());
		for (int i = 0; i < n; ++i) {
			y[i] /= n;
		}
	}
}

// WARN: resize after use!!!
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<complex<ld>> A(a.begin(), a.end()), B(b.begin(), b.end());
	int n = 1;
	while (n < a.size() + b.size()) n <<= 1;
	A.resize(n), B.resize(n);
	fft(A, false), fft(B, false);
	for (int i = 0; i < n; ++i) {
		A[i] *= B[i];
	}
	fft(A, true);
	vector<int> res(n);
	transform(A.begin(), A.end(), res.begin(), expr(int(round(x.real())), auto&& x));
	res.resize(a.size() + b.size() - 1);
	return res;
}

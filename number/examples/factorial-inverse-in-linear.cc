constexpr int M = MDL;

constexpr int N = 3e6 + 10;
ll fact[N], factrev[N + 1], s[N + 1];

void prep() {
	fact[0] = factrev[0] = 1;
	for (int i = 1; i < N; ++i) {
		fact[i] = (fact[i - 1] * i) % M;
	}
	s[0] = 1;
	for (int i = 1; i <= N; ++i) {
		s[i] = s[i - 1] * fact[i - 1] % M;
	}
	factrev[N] = inverse(s[N], M);
	for (int i = N; i; --i) {
		factrev[i - 1] = factrev[i] * fact[i - 1] % M;
	}
	for (int i = 0; i < N; ++i) {
		factrev[i] = factrev[i + 1] * s[i] % M;
	}
}

ll mycomb(int n, int k) {
	if (n < 0 or k < 0 or n < k) return 0;
	return fact[n] * factrev[k] % M * factrev[n - k] % M;
}

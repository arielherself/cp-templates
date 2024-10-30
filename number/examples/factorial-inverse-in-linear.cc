constexpr int N = 3e6 + 10;
ll fact[N], factrev[N + 1], s[N + 1];

void prep() {
    fact[0] = factrev[0] = 1;
    for (int i = 1; i < N; ++i) {
        fact[i] = (fact[i - 1] * i) % MDL;
    }
    s[0] = 1;
    for (int i = 1; i <= N; ++i) {
        s[i] = s[i - 1] * fact[i - 1] % MDL;
    }
    factrev[N] = inverse(s[N], MDL);
    for (int i = N; i; --i) {
        factrev[i - 1] = factrev[i] * fact[i - 1] % MDL;
    }
    for (int i = 0; i < N; ++i) {
        factrev[i] = factrev[i + 1] * s[i] % MDL;
    }
}

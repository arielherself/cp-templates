template <ll M>
void ntt(vector<MLL<M>>& y, bool idft) {
    using mll = MLL<M>;

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
    vector<mll> roots = { 0, 1 };
    if (roots.size() < n) {
        int k = lsp(roots.size());
        roots.resize(n);
        for (; (1 << k) < n; ++k) {
            mll e = qpow<mll>(31, 1 << lsp(M - 1) - k - 1);
            for (int i = 1 << k - 1; i < (1 << k); ++i) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * e;
            }
        }
    }
    for (int h = 2; h <= n; h <<= 1) {
        for (int j = 0; j < n; j += h) {
            for (int k = j; k < j + h / 2; ++k) {
                mll u = y[k], t = roots[k - j + h / 2] * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
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

template <ll M>
vector<MLL<M>> multiply(const vector<MLL<M>>& a, const vector<MLL<M>>& b) {
    using mll = MLL<M>;

    vector<mll> A(a.begin(), a.end()), B(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    A.resize(n), B.resize(n);
    ntt<M>(A, false), ntt<M>(B, false);
    for (int i = 0; i < n; ++i) {
        A[i] *= B[i];
    }
    ntt<M>(A, true);
    return A;
}

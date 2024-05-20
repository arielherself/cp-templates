vector<int> soe(int n) {
    vector<bool> not_prime(n + 1);
    vector<int> res;
    for (int i = 2; i <= n; ++i) {
        if (not not_prime[i]) {
            res.emplace_back(i);
        }
        for (auto&& x : res) {
            if (i * x > n) break;
            not_prime[i * x] = 1;
            if (i % x == 0) break;
        }
    }
    return res;
}

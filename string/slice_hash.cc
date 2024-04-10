struct slice_hash {
    using hash_type = pair<MLL<MDL1>, MLL<MDL2>>;
    int n;
    vector<MLL<MDL1>> pw1;
    vector<MLL<MDL2>> pw2;
    vector<MLL<MDL1>> hash1;
    vector<MLL<MDL2>> hash2;
    slice_hash(const string& s) : n(s.size()), pw1(n + 1), pw2(n + 1), hash1(n + 1), hash2(n + 1) {
        constexpr int b = 31;
        pw1[0] = 1, pw2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            hash1[i] = hash1[i - 1] + s[i - 1] * pw1[i - 1];
            hash2[i] = hash2[i - 1] + s[i - 1] * pw2[i - 1];
            pw1[i] = pw1[i - 1] * b;
            pw2[i] = pw2[i - 1] * b;
        }
    }

    // query [l, r]
    hash_type hash(int l, int r) {
        return { (hash1[r + 1] - hash1[l]) / pw1[l], (hash2[r + 1] - hash2[l]) / pw2[l] };
    }
};

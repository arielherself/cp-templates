static vector<ll> power1, power2;
static const ll b = rd();
static const ll INV1 = inverse(b, MDL1);
static const ll INV2 = inverse(b, MDL2);
template <typename _Tp, typename _Sequence = deque<_Tp>>
struct hash_deque {
    using hash_type = pll;
    ll hash1, hash2;
    _Sequence seq;
    size_t size() {
        return seq.size();
    }
    void push_back(const _Tp& x) {
        hash1 = mod(mod(hash1 * b, MDL1) + mod(x, MDL1), MDL1);
        hash2 = mod(mod(hash2 * b, MDL2) + mod(x, MDL2), MDL2);
        seq.push_back(x);
    }
    void push_front(const _Tp& x) {
        size_t length = size();
        hash1 = mod(hash1 + mod(mod(x, MDL1) * power1[length], MDL1), MDL1);
        hash2 = mod(hash2 + mod(mod(x, MDL2) * power2[length], MDL2), MDL2);
        seq.push_front(x);
    }
    void pop_back() {
        _Tp e = seq.back(); seq.pop_back();
        hash1 = mod(mod(hash1 - mod(e, MDL1), MDL1) * INV1, MDL1);
        hash2 = mod(mod(hash2 - mod(e, MDL2), MDL2) * INV2, MDL2);
    }
    void pop_front() {
        _Tp e = seq.front(); seq.pop_front();
        int length = seq.size();
        hash1 = mod(hash1 - mod(e * power1[length], MDL1), MDL1);
        hash2 = mod(hash2 - mod(e * power2[length], MDL2), MDL2);
    }
    hash_type hash() {
        return {hash1, hash2};
    }
    void clear() {
        hash1 = hash2 = 0;
        seq.clear();
    }
    hash_deque(size_t maxn) {
        clear();
        int c1 = 1, c2 = 1;
        for (int i = power1.size(); i < maxn; ++i) {
            power1.push_back(c1);
            power2.push_back(c2);
            c1 = mod(c1 * b, MDL1);
            c2 = mod(c2 * b, MDL2);
        }
    }
};

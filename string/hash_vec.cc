static vector<MLL<MDL1>> power1;
static vector<MLL<MDL2>> power2;
static const ll b = rd();
template <typename _Tp>
struct hash_vec {
    using hash_type = pll;
    MLL<MDL1> hash1;
    MLL<MDL2> hash2;
    vector<_Tp> seq;
    size_t size() {
        return seq.size();
    }
    void push_back(const _Tp& x) {
        hash1 = hash1 * b + x;
        hash2 = hash2 * b + x;
        seq.push_back(x);
    }
    void push_front(const _Tp& x) {
        size_t length = size();
        hash1 += x * power1[length];
        hash2 += x * power2[length];
        seq.push_front(x);
    }
    void pop_back() {
        _Tp e = seq.back(); seq.pop_back();
        hash1 = (hash1 - e) / b;
        hash2 = (hash2 - e) / b;
    }
    void pop_front() {
        _Tp e = seq.front(); seq.pop_front();
        int length = seq.size();
        hash1 -= e * power1[length];
        hash2 -= e * power2[length];
    }
    void set(size_t pos, const _Tp& value) {
        int length = seq.size();
        int old_value = seq[pos];
        hash1 += (value - old_value) * power1[length - 1 - pos];
        hash2 += (value - old_value) * power2[length - 1 - pos];
        seq[pos] = value;
    }
    const _Tp& operator[](size_t pos) {
        return seq[pos];
    }
    hash_type hash() {
        return {hash1.val, hash2.val};
    }
    void clear() {
        hash1 = 0;
        hash2 = 0;
        seq.clear();
    }
    hash_vec(size_t maxn) {
        clear();
        MLL<MDL1> c1 = power1.size() ? power1.back() * b : 1;
        MLL<MDL2> c2 = power2.size() ? power2.back() * b : 1;
        for (int i = power1.size(); i < maxn; ++i) {
            power1.push_back(c1);
            power2.push_back(c2);
            c1 *= b;
            c2 *= b;
        }
    }
    hash_vec(size_t maxn, const _Tp& init_value) : hash_vec(maxn) {
        for (size_t i = 0; i != maxn; ++i) {
            push_back(init_value);
        }
    }
};

struct range_hash {
    vector<pair<MLL<MDL1>, MLL<MDL2>>> hp;
    template <typename T>
    range_hash(const T& vec) {
        hp.emplace_back();
        hash_vec<ll> hs(vec.size() + 1);
        for (auto&& x : vec) {
            hs.push_back(x);
            hp.emplace_back(hs.hash());
        }
    }

    /// query hash of subarray [l, r]. Index starts from 0.
    pair<MLL<MDL1>, MLL<MDL2>> range_query(size_t l, size_t r) {
        return {
            (hp[r + 1].first - hp[l].first * power1[r + 1 - l]),
            (hp[r + 1].second - hp[l].second * power2[r + 1 - l]),
        };
    }
};


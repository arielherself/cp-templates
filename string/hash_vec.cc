static vector<ll> power1;
static vector<ll> power2;
static const ll b = rd() % INF;
static const ll b1 = inverse(b, MDL1);
static const ll b2 = inverse(b, MDL2);
template <typename _Tp>
struct hash_vec {
	using hash_type = pll;
	ll hash1;
	ll hash2;
	vector<_Tp> seq;
	size_t size() {
		return seq.size();
	}
	void push_back(const _Tp& x) {
		hash1 = (hash1 * b % MDL1 + x) % MDL1;
		hash2 = (hash2 * b % MDL2 + x) % MDL2;
		seq.push_back(x);
	}
	void push_front(const _Tp& x) {
		size_t length = size();
		hash1 = (hash1 + x * power1[length] % MDL1) % MDL1;
		hash2 = (hash2 + x * power2[length] % MDL2) % MDL2;
		seq.push_front(x);
	}
	void pop_back() {
		_Tp e = seq.back(); seq.pop_back();
		hash1 = mod(hash1 - e, MDL1) * b1 % MDL1;
		hash2 = mod(hash2 - e, MDL2) * b2 % MDL2;
	}
	void pop_front() {
		_Tp e = seq.front(); seq.pop_front();
		int length = seq.size();
		hash1 = mod(hash1 - e * power1[length] % MDL1, MDL1);
		hash2 = mod(hash2 - e * power2[length] % MDL2, MDL2);
	}
	void set(size_t pos, const _Tp& value) {
		int length = seq.size();
		int old_value = seq[pos];
		hash1 = (hash1 + (value - old_value) * power1[length - 1 - pos] % MDL1) % MDL1;
		hash2 = (hash2 + (value - old_value) * power2[length - 2 - pos] % MDL2) % MDL2;
		seq[pos] = value;
	}
	const _Tp& operator[](size_t pos) {
		return seq[pos];
	}
	hash_type hash() {
		return { hash1, hash2 };
	}
	void clear() {
		hash1 = 0;
		hash2 = 0;
		seq.clear();
	}
	hash_vec(size_t maxn) {
		clear();
		ll c1 = power1.size() ? power1.back() * b % MDL1 : 1;
		ll c2 = power2.size() ? power2.back() * b % MDL2 : 1;
		for (int i = power1.size(); i < maxn; ++i) {
			power1.push_back(c1);
			power2.push_back(c2);
			c1 = c1 * b % MDL1;
			c2 = c2 * b % MDL2;
		}
	}
	hash_vec(size_t maxn, const _Tp& init_value) : hash_vec(maxn) {
		for (size_t i = 0; i != maxn; ++i) {
			push_back(init_value);
		}
	}
};
struct range_hash {
	vector<pll> hp;
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
	inline pll range_query(size_t l, size_t r) {
		return {
			mod(hp[r + 1].first - hp[l].first * power1[r + 1 - l] % MDL1, MDL1),
			mod(hp[r + 1].second - hp[l].second * power2[r + 1 - l] % MDL2, MDL2),
		};
	}
};

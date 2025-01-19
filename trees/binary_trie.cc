template <int N, typename DataT = int>
struct binary_trie {
	vector<tuple<array<int, 2>, DataT, array<int, 2>>> tr;
	binary_trie() : tr(1) {}
	void emplace(ll x, const DataT& data = {}) {
		int ptr = 0;
		for (int i = N - 1; ~i; --i) {
			int bit = x >> i & 1;
			if (not std::get<0>(tr[ptr])[bit]) {
				std::get<0>(tr[ptr])[bit] = tr.size();
				tr.emplace_back();
			}
			std::get<2>(tr[ptr])[bit] += 1;
			ptr = std::get<0>(tr[ptr])[bit];
		}
		std::get<1>(tr[ptr]) = data;
	}

	/// WARN: Don't try to erase a non-existent element!
	void erase(ll x) {
		int ptr = 0;
		vector<pii> st;
		for (int i = N - 1; ~i; --i) {
			int bit = x >> i & 1;
			st.emplace_back(ptr, bit);
			ptr = std::get<0>(tr[ptr])[bit];
		}
		while (st.size() and std::get<2>(tr[st.back().first])[st.back().second] == 1) {
			std::get<0>(tr[st.back().first])[st.back().second] = 0;
			std::get<2>(tr[st.back().first])[st.back().second] = 0;
			st.pop_back();
		}
		tr[ptr] = {};
	}

	optional<DataT> get(ll x) {
		int ptr = 0;
		for (int i = N - 1; ~i; --i) {
			int bit = x >> i & 1;
			if (not std::get<0>(tr[ptr])[bit]) return {};
			ptr = std::get<0>(tr[ptr])[bit];
		}
		return { std::get<1>(tr[ptr]) };
	}

	int count_prefix(ll x, int bits = N) {
		int ptr = 0;
		int res = 0;
		for (int i = N - 1; i > max(-1, N - 1 - bits); --i) {
			int bit = x >> 1 & 1;
			if (not std::get<0>(tr[ptr])[bit]) return 0;
			ptr = std::get<0>(tr[ptr])[bit];
			res = std::get<2>(tr[ptr])[bit];
		}
		return res;
	}

	optional<pair<ll, DataT&>> get_max_xor(ll x) {
		int ptr = 0;
		ll res = 0;
		for (int i = N - 1; ~i; --i) {
			int bit = x >> i & 1;
			if (std::get<0>(tr[ptr])[1 ^ bit]) {
				ptr = std::get<0>(tr[ptr])[1 ^ bit];
				res |= (1 ^ bit) << i;
			} else if (std::get<0>(tr[ptr])[bit]) {
				ptr = std::get<0>(tr[ptr])[bit];
				res |= bit << i;
			} else {
				return {};
			}
		}
		return {{ res, std::get<1>(tr[ptr]) }};
	}
};

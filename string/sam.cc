template <size_t N>
struct SAM {
	vector<int> fa, len;
	vector<bool> cloned;
	vector<int> cnt;
	vector<array<int, N>> ch;
	int last;
	int tot;

	int create(int _fa, int _len, bool _cloned, array<int, N>&& _ch) {
		fa.emplace_back(_fa);
		len.emplace_back(_len);
		cloned.emplace_back(_cloned);
		ch.emplace_back(_ch);
		return tot++;
	}

	SAM(void) : fa(2), len(2), cloned(2), ch(2), last(1), tot(2) {}

	void push_back(size_t c) {
		int p = last;
		int nw = create(0, len[p] + 1, false, {});

		while (p != 0 and ch[p][c] == 0) {
			ch[p][c] = nw;
			p = fa[p];
		}

		if (p == 0) {
			fa[nw] = 1;
		} else {
			int q = ch[p][c];
			if (len[q] == len[p] + 1) {
				fa[nw] = q;
			} else {
				int nq = create(fa[q], len[p] + 1, true, array(ch[q]));
				fa[nw] = fa[q] = nq;
				while (p != 0 and ch[p][c] == q) {
					ch[p][c] = nq;
					p = fa[p];
				}
			}
		}

		last = nw;
	}

	template <typename T>
	optional<int> find(const basic_string<T>& seq) {
		int p = 1;
		for (auto&& c : seq) {
			if (ch[p][c] == 0) {
				return nullopt;
			}
			p = ch[p][c];
		}
		return p;
	}

	// Fill `cnt` with the number of occurrences of each substring.
	void populate(void) {
		cnt.assign(tot, 0);
		vector<int> idx(tot);
		iota(idx.begin(), idx.end(), 0);
		sort_by_key(idx.begin(), idx.end(), expr(len[i], auto&& i), greater());
		for (auto&& v : idx) {
			if (v > 1 and not cloned[v]) {
				cnt[v] += 1;
			}
			cnt[fa[v]] += cnt[v];
		}
	}
};

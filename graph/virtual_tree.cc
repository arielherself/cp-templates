// BUG: unchecked code
struct virtual_tree {
	int n, root;
	vector<vector<pil>> e;
	LCA lca;
	vector<int> dfn;
	vector<ll> ps;
	virtual_tree(const vector<vector<pil>>& e, int root) : n(e.size() - 1), root(root), e(e), lca(vector<vector<int>> {{}, {}}), dfn(n + 1), ps(n + 1) {
		vector<vector<int>> ch(n + 1);
		for (int u = 0; u <= n; ++u) {
			for (auto&& [v, w] : e[u]) {
				ch[u].emplace_back(v);
			}
		}
		lca = LCA(ch);
		int t = 0;
		auto dfs = [&] (auto dfs, int v, int pa) -> void {
			dfn[v] = ++t;
			for (auto&& [u, w] : e[v]) {
				if (u == pa) continue;
				ps[u] = ps[v] + w;
				dfs(dfs, u, v);
			}
		};
		dfs(dfs, root, 0);
	}
	// vertex number starts from 0
	pair<vector<vector<pil>>, vector<int>> generate(vector<int> pivots) {
		int m = pivots.size();
		if (m == 0) return {};
		sort_by_key(pivots.begin(), pivots.end(), expr(dfn[v], int v));
		vector<int> a;
		for (int i = 0; i < m - 1; ++i) {
			int v = pivots[i];
			int u = lca.query(pivots[i], pivots[i + 1]);
			a.emplace_back(v);
			a.emplace_back(u);
		}
		a.emplace_back(pivots[m - 1]);
		sort_by_key(a.begin(), a.end(), expr(dfn[v], int v));
		m = unique(a.begin(), a.end()) - a.begin();
		unordered_map<int, int, safe_hash> mp;
		vector<int> rev(m);
		for (int i = 0;  i < m; ++i) {
			mp[a[i]] = i;
			rev[i] = a[i];
		}
		vector<vector<pil>> ret(m);
		for (int i = 0; i < m - 1; ++i) {
			int l = lca.query(a[i], a[i + 1]);
			edgew(ret, mp[l], i + 1, ps[a[i + 1]] - ps[l]);
		}
		return { ret, rev };
	}
};

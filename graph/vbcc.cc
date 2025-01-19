// WARN: Input could contain multiple edges, but not self loops
//
// Returns: (BCC count, indices of BCCs of each vertex)
//
// BCC index starts from 1
pair<int, vector<vector<int>>> vbcc(const vector<vector<int>>& ch) {
	int n = ch.size() - 1;
	vector<vector<int>> c(n + 1);  // a vertex could be contained in multiple vBCCs

	int tm = 0;
	int cnt = 0;

	vector<int> low(n + 1), dfn(n + 1);
	vector<int> stack;
	auto dfs = [&] (auto dfs, int v, int pa) -> void {
		int son = 0;
		low[v] = dfn[v] = ++tm;
		stack.emplace_back(v);
		for (auto&& u : ch[v]) {
			if (u == pa) continue;
			son += 1;
			if (not dfn[u]) {
				dfs(dfs, u, v);
				chmin(low[v], low[u]);
				if (low[u] >= dfn[v]) {
					cnt += 1;
					int z;
					do {
						z = popback(stack);
						c[z].emplace_back(cnt);
					} while (z != u);
					c[v].emplace_back(cnt);
				}
			}
			chmin(low[v], dfn[u]);
		}
		if (pa == 0 and son == 0) {
			cnt += 1;
			c[v].emplace_back(cnt);
		}
	};
	for (int i = 1; i <= n; ++i) {
		if (not dfn[i]) {
			dfs(dfs, i, 0);
		}
	}
	return { cnt, c };
}

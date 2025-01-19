// WARN: Input should be a simple graph
//
// Returns: (BCC count, indices of BCC of each vertex)
//
// BCC index starts from 1
pair<int, vector<int>> ebcc(const vector<vector<int>>& ch) {
	int n = ch.size() - 1;
	vector<int> c(n + 1);

	vector<int> low(n + 1), dfn(n + 1);
	vector<bool> vis(n + 1);
	vector<int> stack;

	int time = 0;
	int cnt = 0;

	auto dfs = [&] (auto dfs, int v, int pa) -> void {
		low[v] = dfn[v] = ++time;
		stack.emplace_back(v);
		vis[v] = 1;
		for (auto&& u : ch[v]) {
			if (u == pa) continue;
			if (not dfn[u]) {
				dfs(dfs, u, v);
				chmin(low[v], low[u]);
			} else if (vis[u]) {
				chmin(low[v], dfn[u]);
			}
		}
		if (dfn[v] == low[v]) {
			cnt += 1;
			c[v] = cnt;
			while (stack.back() != v) {
				c[stack.back()] = cnt;
				vis[stack.back()] = 0;
				stack.pop_back();
			}
			stack.pop_back();
		}
	};

	for (int i = 1; i <= n; ++i) {
		if (not dfn[i]) {
			dfs(dfs, i, 0);
		}
	}
	return { cnt, c };
}


// INFO: This function treats vertex pairs that have multiple edges as eBCCs.
//
// Returns: (BCC count, indices of BCC of each vertex)
//
// BCC index starts from 1
pair<int, vector<int>> ebcc_with_mult(const vector<vector<pii>>& ch) {
	int n = ch.size() - 1;
	vector<int> c(n + 1);

	vector<int> low(n + 1), dfn(n + 1);
	vector<bool> vis(n + 1);
	vector<int> stack;

	int time = 0;
	int cnt = 0;

	auto dfs = [&] (auto dfs, int v, int prev_idx) -> void {
		low[v] = dfn[v] = ++time;
		stack.emplace_back(v);
		vis[v] = 1;
		for (auto&& [u, i] : ch[v]) {
			if (i == prev_idx) continue;
			if (not dfn[u]) {
				dfs(dfs, u, i);
				chmin(low[v], low[u]);
			} else if (vis[u]) {
				chmin(low[v], dfn[u]);
			}
		}
		if (dfn[v] == low[v]) {
			cnt += 1;
			c[v] = cnt;
			while (stack.back() != v) {
				c[stack.back()] = cnt;
				vis[stack.back()] = 0;
				stack.pop_back();
			}
			stack.pop_back();
		}
	};

	for (int i = 1; i <= n; ++i) {
		if (not dfn[i]) {
			dfs(dfs, i, -1);
		}
	}
	return { cnt, c };
}

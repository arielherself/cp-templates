struct mcmf {
	struct edge {
		int to;
		ll cap;
		ll flow;
		ll cost;
		int rev;
		int mark;
	};
	vector<vector<edge>> edges;
	vector<ll> dis;
	vector<bool> vis;
	ll ret;
	mcmf(int n) : edges(n + 1), dis(n + 1), vis(n + 1) {}
	void add_edge(int from, int to, ll cap, ll cost, int mark = 0, int mark_rev = 0) {
		edges[from].push_back({ to, cap, 0, cost, int(edges[to].size()), mark });
		edges[to].push_back({ from, 0, 0, -cost, int(edges[from].size() - 1), mark_rev });
	}
	bool sp(int s, int t) {
		dis.assign(edges.size(), INFLL);
		dis[s] = 0;
		int n = edges.size();
		int f = 1;
		while (f) {
			f = 0;
			for (int i = 0; i < n; ++i) {
				for (auto&& [to, cap, flow, cost, rev, mark] : edges[i]) {
					if (cap > flow and dis[to] > dis[i] + cost) {
						dis[to] = dis[i] + cost;
						f = 1;
					}
				}
			}
		}
		return dis[t] != INFLL;
	}
	ll dfs(int s, int t, ll cap) {
		if (vis[s]) {
			return 0;
		}
		vis[s] = 1;
		if (s == t) {
			return cap;
		}
		ll res = 0;
		int n = edges[s].size();
		for (int i = 0; i < n; ++i) {
			auto e = edges[s][i];
			if (e.cap > e.flow and dis[e.to] == dis[s] + e.cost) {
				ll nw = dfs(e.to, t, min(cap - res, e.cap - e.flow));
				edges[s][i].flow += nw;
				edges[e.to][e.rev].flow -= nw;
				res += nw;
				ret += nw * e.cost;
				if (res == cap) {
					return res;
				}
			}
		}
		return res;
	}
	// returns: (flow, cost)
	pll run(int s, int t) {
		ll res = 0; ret = 0;
		while (sp(s, t)) {
			vis.assign(edges.size(), 0);
			ll curr = dfs(s, t, LLONG_MAX);
			res += curr;
			// BUG: this is a temporary fix of the infinite-looping issue observed
			// when dealing with networks with negative weights.
			if (curr == 0) break;
		}
		return { res, ret };
	}
};

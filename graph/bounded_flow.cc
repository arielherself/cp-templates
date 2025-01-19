struct bounded_flow {
	int n, m, S, T;
	dinic net;
	ll sum;
	vector<ll> fl;
	vector<ll> init;
	bounded_flow(int n, int m) : sum(0), n(n), m(m), S(0), T(n + 1), net(n + 1), fl(m), init(n + 1) {}
	void add_edge(int from, int to, ll low, ll high, int edge_id = -1) {
		if (edge_id != -1) {
			fl[edge_id] += low;
		}
		net.add_edge(from, to, high - low, edge_id, -1);
		init[to] += low, init[from] -= low;
	}
	void prep(int s, int t) {
		for (int i = 1; i <= n; ++i) {
			if (init[i] > 0) {
				net.add_edge(S, i, init[i], -1, -1);
				sum += init[i];
			} else if (init[i] < 0) {
				net.add_edge(i, T, -init[i], -1, -1);
			}
		}
		net.add_edge(t, s, INFLL, INF, -1);
	}
	optional<pair<ll, vector<ll>>> run_max_flow(int s, int t) {
		prep(s, t);
		if (sum != net.run(S, T)) {
			return nullopt;
		} else {
			auto res_flow = net.run(s, t);
			for (int from = 1; from <= n; ++from) {
				for (auto&& [to, cap, flow, rev, mark] : net.edges[from]) {
					if (mark != -1 and mark != INF) {
						fl[mark] += flow;
					}
				}
			}
			return {{res_flow, fl}};
		}
	}
	optional<pair<ll, vector<ll>>> run_min_flow(int s, int t) {
		prep(s, t);
		if (sum != net.run(S, T)) {
			return nullopt;
		} else {
			int curr;
			for (int i = 0; i < m; ++i) {
				if (net.edges[t][i].mark == INF) {
					net.edges[t][i].cap = 0;
					net.edges[net.edges[t][i].to][net.edges[t][i].rev].cap = 0;
					curr = net.edges[t][i].flow;  // WARN: real flow
					break;
				}
			}
			curr -= net.run(t, s);
			for (int from = 1; from <= n; ++from) {
				for (auto&& [to, cap, flow, rev, mark] : net.edges[from]) {
					if (mark != -1 and mark != INF) {
						fl[mark] += flow;
					}
				}
			}
			return {{curr, fl}};
		}
	}
	optional<pair<ll, vector<ll>>> run_flow(int s, int t) {  // BUG: unchecked code
		prep(s, t);
		auto res_flow = net.run(S, T);
		if (sum != res_flow) {
			return nullopt;
		} else {
			for (int from = 1; from <= n; ++from) {
				for (auto&& [to, cap, flow, rev, mark] : net.edges[from]) {
					if (mark != -1 and mark != INF) {
						fl[mark] += flow;
					}
				}
			}
			return {{res_flow, fl}};
		}
	}
};

struct bounded_mcmf {
	int n, m, S, T;
	mcmf net;
	ll sum, pre;
	vector<ll> fl;
	vector<ll> init;
	vector<ll> costs;
	bounded_mcmf(int n, int m) : sum(0), pre(0), n(n), m(m), S(0), T(n + 1), net(n + 1), fl(m), init(n + 1), costs(m) {}
	// handle negative loop case
	void add_edge(int from, int to, ll low, ll high, ll cost, int edge_id = -1) {
		if (cost < 0) {
			__add_edge(from, to, high, high, cost, -1);
			__add_edge(to, from, 0, high - low, -cost, edge_id);
		} else {
			__add_edge(from, to, low, high, cost, edge_id);
		}
		if (edge_id != -1) {
			costs[edge_id] = cost;
			if (cost < 0) {
				fl[edge_id] += high;  // RealFlow = UpperBound - Flow
			} else {
				fl[edge_id] += low;   // RealFlow = LowerBound + Flow
			}
		}
	}
	void __add_edge(int from, int to, ll low, ll high, ll cost, int edge_id = -1) {
		net.add_edge(from, to, high - low, cost, edge_id, -1);
		init[to] += low, init[from] -= low;
		pre += low * cost;
	}
	void prep(int s, int t) {
		for (int i = 1; i <= n; ++i) {
			if (init[i] > 0) {
				net.add_edge(S, i, init[i], 0, -1, -1);
				sum += init[i];
			} else if (init[i] < 0) {
				net.add_edge(i, T, -init[i], 0, -1, -1);
			}
		}
		net.add_edge(t, s, INFLL, 0, -1, -1);
	}
	// min-cost max-flow
	optional<tuple<ll, ll, vector<ll>>> run_mcmf(int s, int t) {  // BUG: unchecked code
		prep(s, t);
		if (sum != net.run(S, T).first) {
			return nullopt;
		} else {
			auto [res_flow, res_cost] = net.run(s, t);
			for (int from = 1; from <= n; ++from) {
				for (auto&& [to, cap, flow, cost, rev, mark] : net.edges[from]) {
					if (mark != -1) {
						if (costs[mark] < 0) {
							fl[mark] -= flow;
						} else {
							fl[mark] += flow;
						}
					}
				}
			}
			res_cost += pre;
			return {{res_flow, res_cost, fl}};
		}
	}
	// min-cost flow
	optional<tuple<ll, ll, vector<ll>>> run_mcf(int s, int t) {
		prep(s, t);
		auto [res_flow, res_cost] = net.run(S, T);
		res_cost += pre;
		if (sum != res_flow) {
			return nullopt;
		} else {
			for (int from = 1; from <= n; ++from) {
				for (auto&& [to, cap, flow, cost, rev, mark] : net.edges[from]) {
					if (mark != -1) {
						if (costs[mark] < 0) {
							fl[mark] -= flow;
						} else {
							fl[mark] += flow;
						}
					}
				}
			}
			return {{res_flow, res_cost, fl}};
		}
	}
};

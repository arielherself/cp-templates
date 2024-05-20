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
    optional<pair<ll, vector<ll>>> run(int s, int t) {
        for (int i = 1; i <= n; ++i) {
            if (init[i] > 0) {
                net.add_edge(S, i, init[i], -1, -1);
                sum += init[i];
            } else if (init[i] < 0) {
                net.add_edge(i, T, -init[i], -1, -1);
            }
        }
        net.add_edge(t, s, INFLL, -1, -1);
        if (sum != net.run(S, T)) {
            return nullopt;
        } else {
            auto res_flow = net.run(s, t);
            for (int from = 1; from <= n; ++from) {
                for (auto&& [to, cap, flow, rev, mark] : net.edges[from]) {
                    if (mark != -1) {
                        fl[mark] += flow;
                    }
                }
            }
            return {{res_flow, fl}};
        }
    }
};

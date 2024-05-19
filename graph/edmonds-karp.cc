struct edmonds_karp {
    struct edge {
        int to;
        ll cap;
        ll flow;
        pair<int, int> rev;
        int mark;
    };

    vector<vector<edge>> edges;

    edmonds_karp(int n) : edges(n + 1) {}

    void add_edge(int from, int to, ll cap, int mark = false) {
        edges[from].push_back({to, cap, 0, make_pair(to, int(edges[to].size())), mark});
        edges[to].push_back({from, 0, 0, make_pair(from, int(edges[from].size() - 1)), mark});
    }

    ll run(int s, int t) {
        int n = edges.size();
        vector<pii> pa_(n + 1);
        ll res = 0;
        while (1) {
            vector<ll> pf(n + 1);
            deque<int> dq;
            dq.emplace_back(s);
            pf[s] = LLONG_MAX;
            while (dq.size()) {
                int v = dq.front(); dq.pop_front();
                for (auto&& [i, ne] : enumerate(edges[v])) {
                    if (pf[ne.to] == 0 and ne.cap > ne.flow) {
                        pf[ne.to] = min(pf[v], ne.cap - ne.flow);
                        pa_[ne.to] = {v, i};
                        dq.emplace_back(ne.to);
                    }
                }
                if (pf[t] != 0) {
                    break;
                }
            }
            if (pf[t] == 0) {
                break;
            }
            int p = t;
            while (pa_[p].first != 0) {
                auto [x, y] = pa_[p];
                edges[x][y].flow += pf[t];
                auto [z, w] = edges[x][y].rev;
                edges[z][w].flow -= pf[t];
                p = x;
            }
            res += pf[t];
        }
        return res;
    }
};

struct dinic {
    struct edge {
        int to;
        ll cap;
        ll flow;
        int rev;
        int mark;
    };

    vector<vector<edge>> edges;
    vector<int> layer;
    vector<bool> vis;

    dinic(int n) : edges(n + 1), layer(n + 1), vis(n + 1) {}

    void add_edge(int from, int to, ll cap, int mark = false) {
        edges[from].push_back({ to, cap, 0, int(edges[to].size()), mark });
        edges[to].push_back({ from, 0, 0, int(edges[from].size() - 1), mark });
    }

    bool bfs(int s, int t) {
        layer.assign(edges.size(), 0);
        deque<pii> dq;
        layer[s] = 1;
        dq.emplace_back(s, 1);
        while (dq.size()) {
            popfront(dq, v, l);
            for (auto&& e : edges[v]) {
                if (layer[e.to] == 0 and e.cap > e.flow) {
                    layer[e.to] = l + 1;
                    dq.emplace_back(e.to, l + 1);
                }
            }
        }
        return layer[t] != 0;
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
            if (e.cap > e.flow and layer[e.to] == layer[s] + 1) {
                ll nw = dfs(e.to, t, min(cap - res, e.cap - e.flow));
                edges[s][i].flow += nw;
                edges[e.to][e.rev].flow -= nw;
                res += nw;
                if (res == cap) {
                    return res;
                }
            }
        }
        return res;
    }

    ll run(int s, int t) {
        ll res = 0;
        while (bfs(s, t)) {
            vis.assign(edges.size(), 0);
            res += dfs(s, t, LLONG_MAX);
        }
        return res;
    }
};

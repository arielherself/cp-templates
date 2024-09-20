struct hierholzer {
    struct edge_t {
        int from, to, rev, stale;
        edge_t(int from, int to, int rev, int stale) : from(from), to(to), rev(rev), stale(stale) {}
    };
    int n;
    vector<edge_t> edges;
    vector<vector<int>> ch;
    quick_union qu;

    hierholzer(int n) : n(n), ch(n + 1), qu(n + 1) {}

    void add_edge(int u, int v) {
        int left = edges.size(), right = left + 1;
        edges.emplace_back(u, v, right, false);
        edges.emplace_back(v, u, left, false);
        ch[u].emplace_back(left);
        ch[v].emplace_back(right);
        qu.merge(u, v);
    }

    optional<vector<int>> solve() {
        if (qu.query_size(1) != n) {
            return nullopt;
        }

        int odd = 0;
        int last_odd;
        for (int i = 1; i <= n; ++i) {
            if (ch[i].size() % 2) {
                odd += 1;
                last_odd = i;
            }
        }

        int start;
        if (odd == 0) {
            start = 1;
        } else if (odd == 2) {
            start = last_odd;
        } else {
            return nullopt;
        }

        vector<int> res;

        auto dfs = [&] (auto&& dfs, int v) -> void {
            while (ch[v].size()) {
                int i = ch[v].back();
                ch[v].pop_back();
                if (not edges[i].stale) {
                    edges[i].stale = true;
                    edges[edges[i].rev].stale = true;
                    dfs(dfs, edges[i].to);
                }
            }
            res.emplace_back(v);
        };
        dfs(dfs, start);

        return res;
    }
};

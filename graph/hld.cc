namespace HLD {
    struct node_info {
        int father, depth, hson, size, head, dfn = -1;
    };

    // returns: (dfs sequence, node info)
    // node numbering starts from `1`
    // if `dfn(v) == -1`, then node `v` is never accessed.
    pair<vector<int>, vector<node_info>> work(int n, const vector<vector<int>>& ch, int root = 0) {
        vector<int> seq;
        vector<node_info> res(n + 1);
        auto dfs1 = [&] (auto dfs1, int v, int pa) -> void {
            res[v].father = pa;
            res[v].depth = res[pa].depth + 1;
            res[v].size = 1;
            int mx = 0;
            for (auto&& u : ch[v]) {
                if (u == pa) continue;
                dfs1(dfs1, u, v);
                res[v].size += res[u].size;
                if (res[u].size > mx) {
                    mx = res[u].size;
                    res[v].hson = u;
                }
            }
        };
        dfs1(dfs1, root, root);
        int tm = 0;
        auto dfs2 = [&] (auto dfs2, int v, int head) -> void {
            res[v].dfn = tm++;
            seq.emplace_back(v);
            res[v].head = head;
            if (not res[v].hson) return;
            dfs2(dfs2, res[v].hson, head);
            for (auto&& u : ch[v]) {
                if (u == res[v].father or u == res[v].hson) continue;
                dfs2(dfs2, u, u);
            }
        };
        dfs2(dfs2, root, root);
        return { seq, res };
    }
}

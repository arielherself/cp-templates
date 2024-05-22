template <typename Info, typename Tag>
struct HLD {
    struct node_info {
        int father, depth, hson, size, head, dfn = -1;
    };

    int n;
    vector<int> seq;
    vector<node_info> info;
    segtree<Info, Tag> tr;

    // returns: (dfs sequence, node info)
    // node numbering starts from `1`
    // if `dfn(v) == -1`, then node `v` is never accessed.
    HLD(const vector<vector<int>>& ch, const vector<Info>& init, int root = 0) : n(ch.size() - 1), seq(), info(n + 1), tr(n + 1) {
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
        info = res;

        for (int i = 1; i <= n; ++i) {
            tr.set(info[i].dfn, init[i]);
        }
    }

    void set(int v, const Info& t) {
        tr.set(info[v].dfn, t);
    }

    void apply(int v, const Tag& t) {
        tr.apply(info[v].dfn, t);
    }

    Info query(int v) {
        return tr.query(info[v].dfn);
    }

    void path_apply(int u, int v, const Tag& t) {
        while (info[u].head != info[v].head) {
            if (info[info[u].head].depth < info[info[v].head].depth) {
                swap(u, v);
            }
            tr.range_apply(info[info[u].head].dfn, info[u].dfn, t);
        }
        if (info[u].depth < info[v].depth) swap(u, v);
        tr.range_apply(info[v].dfn, info[u].dfn);
    }

    Info path_query(int u, int v) {
        Info res;
        while (info[u].head != info[v].head) {
            if (info[info[u].head].depth < info[info[v].head].depth) {
                swap(u, v);
            }
            res = res + tr.range_query(info[info[u].head].dfn, info[u].dfn);
        }
        if (info[u].depth < info[v].depth) swap(u, v);
        res = res + tr.range_query(info[v].dfn, info[u].dfn);
        return res;
    }

    void subtree_apply(int v, const Tag& t) {
        tr.range_apply(info[v].dfn, info[v].dfn + info[v].size - 1, t);
    }

    Info subtree_query(int v) {
        return tr.range_query(info[v].dfn, info[v].dfn + info[v].size - 1);
    }
};

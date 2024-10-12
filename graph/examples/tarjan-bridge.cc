vector<bool> isbridge(m);
{
    vector<int> low(n + 1), dfn(n + 1), father(n + 1);
    int dfs_clock = 0;
    int cnt_bridge = 0;
    auto dfs = [&] (auto dfs, int u, int fa) -> void {
        father[u] = fa;
        low[u] = dfn[u] = ++dfs_clock;
        for (auto&& [v, i] : ch[u]) {
            if (!dfn[v]) {
                dfs(dfs, v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    isbridge[i] = true;
                    ++cnt_bridge;
                }
            } else if (dfn[v] < dfn[u] && v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };
    for (int i = 1; i <= n; ++i) {
        if (not dfn[i]) dfs(dfs, i, 0);
    }
}

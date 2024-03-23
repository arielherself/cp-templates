struct LCA {
    vector<int> depth;
    vector<vector<int>> pa;
    LCA(const vector<vector<int>>& g, int root = 1) {
        int n = g.size() - 1;
        int m = 32 - __builtin_clz(n);
        depth.resize(n + 1);
        pa.resize(n + 1, vector<int>(m, -1));
        function<void(int, int)> dfs = [&](int x, int fa) {
            pa[x][0] = fa;
            for (int y: g[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    dfs(y, x);
                }
            }
        };
        dfs(root, 0);

        for (int i = 0; i < m - 1; i++)
            for (int x = 1; x <= n; x++)
                if (int p = pa[x][i]; p != -1)
                    pa[x][i + 1] = pa[p][i];
    }

    int get_kth_ancestor(int node, int k) {
        for (; k; k &= k - 1)
            node = pa[node][__builtin_ctz(k)];
        return node;
    }

    int query(int x, int y) {
        if (depth[x] > depth[y])
            swap(x, y);
        y = get_kth_ancestor(y, depth[y] - depth[x]);
        if (y == x)
            return x;
        for (int i = pa[x].size() - 1; i >= 0; i--) {
            int px = pa[x][i], py = pa[y][i];
            if (px != py) {
                x = px;
                y = py;
            }
        }
        return pa[x][0];
    }
};


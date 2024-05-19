// ...

struct dinic {
    // ...
};

void solve() {
    read(int, n, m);
    dinic net(n + 1);
    vector<int> init(n + 1);
    vector<int> res(m);
    for (int i = 0; i < m; ++i) {
        read(int, u, v, lower, upper);
        net.add_edge(u, v, upper - lower, i, -1);
        init[v] += lower;  // in
        init[u] -= lower;  // out
        res[i] += lower;
    }
    for (int i = 1; i <= n; ++i) {
        if (init[i] > 0) {
            net.add_edge(0, i, init[i], -1, -1);
        } else if (init[i] < 0) {
            net.add_edge(i, n + 1, -init[i], -1, -1);
        }
    }
    net.run(0, n + 1);
    for (auto&& [from, e] : enumerate(net.edges)) {
        for (auto&& [to, cap, flow, rev, mark] : e) {
            if ((from == 0 or to == n + 1) and flow != cap) {
                cout << "NO\n";
                return;
            }
            if (mark != -1) {
                res[mark] += flow;
            }
        }
    }
    cout << "YES\n";
    copy(res.begin(), res.end(), oi<int>(cout, "\n"));
}

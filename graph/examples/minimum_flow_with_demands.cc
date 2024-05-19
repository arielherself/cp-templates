struct dinic {
    // ...
};

void solve() {
    read(int, n, m, s, t);
    dinic net(n + 1);
    int S = 0, T = n + 1;
    vector<ll> init(n + 1);
    for (int i = 0 ;i  < m; ++i) {
        read(ll, u, v, lower, upper);
        init[v] += lower;
        init[u] -= lower;
        net.add_edge(u, v, upper - lower);
    }
    ll sum = 0;
    for (int i  =1; i <= n; ++i) {
        if (init[i] > 0) {
            net.add_edge(S, i, init[i]);
            sum += init[i];
        } else if (init[i] < 0) {
            net.add_edge(i, T, -init[i]);
        }
    }
    net.add_edge(t, s, INFLL, 1, 1);  // WARN: s->t is wrong
    if (sum != net.run(S, T)) {
        cout << "please go home to sleep\n";
    } else {
        int m = net.edges[t].size();
        int curr;
        for (int i = 0; i < m; ++i) {
            if (net.edges[t][i].mark) {
                net.edges[t][i].cap = 0;
                net.edges[net.edges[t][i].to][net.edges[t][i].rev].cap = 0;
                curr = net.edges[t][i].flow;  // WARN: real flow
                break;
            }
        }
        cout << curr - net.run(t, s) << '\n';
    }
}

struct dinic {
	// ...
};

void solve() {
	read(int, n, m, s, t);
	dinic net(n + 1);
	int S = 0, T = n + 1;
	vector<int> init(n + 1);
	for (int i = 0 ;i  < m; ++i) {
		read(int, u, v, lower, upper);
		init[v] += lower;
		init[u] -= lower;
		net.add_edge(u, v, upper - lower);
	}
	int sum = 0;
	for (int i	=1; i <= n; ++i) {
		if (init[i] > 0) {
			net.add_edge(S, i, init[i]);
			sum += init[i];
		} else if (init[i] < 0) {
			net.add_edge(i, T, -init[i]);
		}
	}
	net.add_edge(t, s, INF);  // WARN: s->t is wrong
	if (sum != net.run(S, T)) {
		cout << "please go home to sleep\n";
	} else {
		cout << net.run(s, t) << '\n';
	}
}

vector<int> get_phi(int n) {
	vector<bool> not_prime(n + 1);
	vector<int> res;
	vector<int> phi(n + 1);
	phi[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (not not_prime[i]) {
			res.emplace_back(i);
			phi[i] = i - 1;
		}
		for (auto&& x : res) {
			if (i * x > n) break;
			not_prime[i * x] = 1;
			if (i % x == 0) {
				// phi(n) = n * prod((p - 1) / p)
				// => phi(i * x) = i * x * prod((p - 1) / p) = (i * prod((p - 1) / p)) * x = phi(i) * x,
				// since `i` covers all factors of i * x
				phi[i * x] = phi[i] * x;
				break;
			} else {
				// i coprimes x
				// phi(i * x) = phi(i) * phi(x) = phi(i) * (x - 1)
				phi[i * x] = phi[i] * (x - 1);
			}
		}
	}
	return phi;
}

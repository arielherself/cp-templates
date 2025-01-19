pair<vector<int>, vector<int>> factcount(int n) {
	vector<bool> not_prime(n + 1);
	vector<int> res(n + 1), num(n + 1);
	vector<int> primes;
	res[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (not not_prime[i]) {
			res[i] = 2;
			num[i] = 1;
			primes.emplace_back(i);
		}
		for (auto&& x : primes) {
			if (i * x > n) break;
			not_prime[i * x] = 1;
			if (i % x == 0) {
				num[i * x] = num[i] + 1;
				res[i * x] = res[i] / num[i * x] * (num[i * x] + 1);
				break;
			}
			num[i * x] = 1;
			res[i * x] = res[i] * 2;
		}
	}
	return {primes, res};
}

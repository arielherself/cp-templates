// in-place modification
int basis(vector<ll>& a) {
	int n = a.size();
	int has = 0;
	for (int i = 63; ~i and has < n; --i) {
		for (int j = has; j < n; ++j) {
			if (a[j] & (ll(1) << i)) {
				swap(a[j], a[has]);
				break;
			}
		}
		if (not (a[has] & (ll(1) << i))) continue;
		for (int j = 0; j < n; ++j) {
			if (j == has) continue;
			if (a[j] & (ll(1) << i)) {
				a[j] ^= a[has];
			}
		}
		++has;
	}
	return has;
}

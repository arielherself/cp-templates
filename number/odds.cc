auto odds = [] (ll a, ll b) -> ll {
	if (a % 2 == 0) a += 1;
	if (b % 2 == 0) b -= 1;
	if (a > b) return 0;
	ll odd_sum = ((b + 1) / 2) * ((b + 1) / 2) - ((a - 1) / 2) * ((a - 1) / 2);
	return odd_sum;
};
auto oddcount = [] (ll a, ll b) -> ll {
	return (b - a) / 2 + (a & 1 | b & 1);
};

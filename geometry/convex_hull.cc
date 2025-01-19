struct convex_hull {
	int n, m;
	vector<int> on_hull;
	// WARN: counter-clockwise
	vector<int> hull;

	// WARN: sort the points before initializing
	template <typename T>
	convex_hull(const vector<point<T>>& a) : n(a.size()), on_hull(n) {
		for (int i = 0; i < n; ++i) {
			int m = hull.size();
			// WARN: keeping the points that are on edges
			while (m > 1 and (a[hull[m - 1]] - a[hull[m - 2]]) * (a[i] - a[hull[m - 2]]) < 0) {
				on_hull[hull[m - 1]] -= 1;
				hull.pop_back();
				m -= 1;
			}
			on_hull[i] += 1;
			hull.emplace_back(i);
		}
		int low = hull.size();

		for (int i = n - 2; ~i; --i) {
			int m = hull.size();
			while (m > low and (a[hull[m - 1]] - a[hull[m - 2]]) * (a[i] - a[hull[m - 2]]) < 0) {
				on_hull[hull[m - 1]] -= 1;
				hull.pop_back();
				m -= 1;
			}
			on_hull[i] += 1;
			hull.emplace_back(i);
		}
		if (n > 1) {
			hull.pop_back();
		}
		m = hull.size();
	}
};

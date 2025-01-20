struct graham {
	int n, m;
	vector<int> on_hull;
	// WARN: counter-clockwise
	vector<int> hull;

	template <typename T>
	graham(const vector<point<T>>& a) : n(a.size()), on_hull(n) {
		vector<int> idx(n);
		iota(idx.begin(), idx.end(), 0);
		for (int i = 1; i < n; ++i) {
			if (a[i].y < a[idx[0]].y or a[i].y == a[idx[0]].y and a[i].x < a[idx[0]].x) {
				swap(idx[0], idx[i]);
			}
		}
		sort(idx.begin() + 1, idx.end(), [&] (int p, int q) {
			auto cross = (a[p] - a[idx[0]]) * (a[q] - a[idx[0]]);
			if (cross == 0) {
				return (a[p] - a[idx[0]]).norm() < (a[q] - a[idx[0]]).norm();
			} else {
				return cross > 0;
			}
		});
		hull.emplace_back(idx[0]);
		m = hull.size();
		for (int i = 1; i < n; ++i) {
			// if (a[idx[i]] == a[idx[i - 1]]) continue;  // NOTE: uncomment this line to remove duplicate points
			// NOTE: change to leq to remove points on edges
			while (m >= 2 and (a[hull[m - 1]] - a[hull[m - 2]]) * (a[idx[i]] - a[hull[m - 1]]) < 0) {
				hull.pop_back();
				m -= 1;
			}
			hull.emplace_back(idx[i]);
			m += 1;
		}
		for (auto&& i : hull) {
			on_hull[i] = 1;
		}
	}
};


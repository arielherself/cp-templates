// Part of the code from a Cf problem to demonstrate how to dump the path from a knapsack-dp solution.
for (int j = 1; j <= m; ++j) {
    auto [t, p, idx] = events[i][j - 1];
    for (int k = 0; k <= 100; ++k) {
        dp[j][k] = dp[j - 1][k];
    }
    for (int k = 0; k <= 100; ++k) {
        int new_percent = min(100, dp[j - 1][k].second + p);  // In this problem we just omit the capacity over 100.
        if (dp[j][new_percent].first > dp[j - 1][k].first + t) {
            dp[j][new_percent] = {dp[j - 1][k].first + t, dp[j - 1][k].second + p};
        }
    }
}
ll tm = dp[m][100].first;
if (tm + start > a[i]) {
    cout << -1 << '\n';
    return;
} else {
    int k = dp[m][100].second;
    for (int j = m; j >= 1; --j) {
        auto [t, p, idx] = events[i][j - 1];
        if (dp[j][min(100, k)] < dp[j - 1][min(100, k)]) {  // Find the last step of the construction process.
            k -= p;  // Prepare to find the next one.
            res.emplace_back(idx);  // Add the current item as part of the solution.
        }
    }
    start += tm;
}

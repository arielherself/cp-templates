// uoj-78.cc

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(NULL);
    int nl, nr, m;
    cin >> nl >> nr >> m;
    vector<vector<int>> left(nl+1);
    vector<vector<int>> right(nr+1);
    vector<int> choice_left(nl+1);
    vector<int> choice_right(nr+1);
    vector<int> vis(nl+1);
    while(m--) {
        int v, u;
        cin >> v >> u;
        left[v].push_back(u);
        right[u].push_back(v);
    }
    function<bool(int)> dfs = [&](int v) -> bool {
        if (vis[v]) return false;
        vis[v] = true;
        for (auto&& u : left[v]) {
            if (choice_right[u]) {
                int t = choice_right[u];
                if (dfs(t)) {
                    choice_left[v] = u;
                    choice_right[u] = v;
                    vis[v] = false;
                    return true;
                }
            } else {
                choice_left[v] = u;
                choice_right[u] = v;
                vis[v] = false;
                return true;
            }
        }
        return false;
    };
    for (int i = 1; i <= nl; ++i) {
        if (!choice_left[i]) {
            dfs(i);
        }
    }
    vector<int> res;
    int cnt = 0;
    for (int i = 1; i <= nl; ++i) {
        if (choice_left[i]) {
            ++cnt;
        }
        res.push_back(choice_left[i]);
    }
    cout << cnt << endl;
    for (auto&& j : res)
        cout << j << ' ';
}

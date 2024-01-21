#include "../include.hh"

int main() {
    untie;
    read(int, n);
    adj(ch, n);
    for (int i = 0; i < n - 1; ++i) {
        read(int, u, v);
        edge(ch, u, v);
    }
    readvec(int, c, n);  // WARNING


    vector<int> size(n + 1);
    vector<int> heavy(n + 1);
    auto dfs = [&] (auto dfs, int v, int pa) -> int {
        size[v] = 1;
        for (auto&& u : ch[v]) {
            if (u != pa) {
                int curr = dfs(dfs, u, v);
                size[v] += curr;
                if (curr > size[heavy[v]]) heavy[v] = u;
            }
        }
        return size[v];
    };
    dfs(dfs, 1, 0);


    vector<int> cnt(n + 1);
    vector<int> res(n + 1);
    auto remove = [&] (auto remove, int v, int pa) -> void {
        cnt[c[v-1]] -= 1;
        for (auto&& u : ch[v]) if (u != pa) remove(remove, u, v);
    };
    auto dfs2 = [&] (auto dfs2, int v, int pa, int update_ans, int write_cnt) -> int {
        if (!v) return 0;
        if (update_ans) {
            for (auto&& u : ch[v]) {
                if (u != pa && u != heavy[v]) dfs2(dfs2, u, v, 1, 0);
            }
        }
        int ans = dfs2(dfs2, heavy[v], v, update_ans, 1);
        for (auto&& u : ch[v]) {
            if (u != pa && u != heavy[v]) ans += dfs2(dfs2, u, v, 0, 1);
        }
        if (!cnt[c[v-1]]) {
            cnt[c[v-1]] = 1;
            ++ans;
        } else {
            cnt[c[v-1]] += 1;
        }
        // debugvec(cnt);
        if (!write_cnt) {
            remove(remove, v, pa);
        }
        if (update_ans) {
            res[v] = ans;
        }
        return ans;
    };
    dfs2(dfs2, 1, 0, 1, 1);


    read(int, m);
    while(m--) {
        read(int, q);
        cout << res[q] << endl;
    }
}

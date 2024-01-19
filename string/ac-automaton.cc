#include "../include.hh"

void solve(vector<string> ss, string t) {
    int n = ss.size();
    vector<vector<int>> trie(1, vector<int>(26));
    vector<int> tag(1);
    vector<int> id(1);
    vector<int> alias(n, -1);
    int last = 0;
    // build trie for ss
    for (int i = 0; i < n; ++i) {
        auto&& s = ss[i];
        int curr = 0;
        for (auto&& c : s) {
            int x = c - 'a';
            if (!trie[curr][x])
                trie[curr][x] = ++last,
                tag.push_back({}),
                id.push_back({}),
                trie.push_back(vector<int>(26));
            curr = trie[curr][x];
        }
        if (!tag[curr]) id[curr] = i;
        else alias[i] = id[curr];
        tag[curr] = 1;
    }


    // build fail
    vector<int> fail(last + 1);
    vector<vector<int>> suc(last + 1);
    deque<pair<int, int>> dq;
    for (int i = 0; i < 26; ++i) {
        if (trie[0][i]) dq.emplace_back(trie[0][i], trie[0][i]), suc[0].push_back(trie[0][i]);
    }
    while (dq.size()) {
        popfront(dq, c, rt);
        for (int i = 0; i < 26; ++i) {
            if (trie[c][i]) {
                fail[trie[c][i]] = trie[fail[c]][i];
                suc[trie[fail[c]][i]].push_back(trie[c][i]);
                dq.emplace_back(trie[c][i], rt);
            } else {
                trie[c][i] = trie[fail[c]][i];
            }
        }
    }


    // match t
    vector<int> oc(last + 1);
    int curr = 0;
    for (auto&& c : t) {
        int x = c - 'a';
        if (!trie[curr][x]) curr = fail[curr];
        curr = trie[curr][x];
        oc[curr] += 1;
    }


    // collect result
    vector<int> res(n);
    auto dfs = [&] (auto dfs, int cur) -> int {
        int cnt = oc[cur];
        for (auto&& c : suc[cur]) {
            cnt += dfs(dfs, c);
        }
        if (cnt && tag[cur]) {
            res[id[cur]] += cnt;
        }
        return cnt;
    };
    dfs(dfs, 0);
    for (int i = 0; i < n; ++i) {
        if (alias[i] != -1) cout << res[alias[i]];
        else cout << res[i];
        cout << endl;
    }
}

int main() {
    read(int, n);
    readvec(string, ss, n);
    read(string, t);
    solve(ss, t);
}

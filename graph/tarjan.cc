namespace tarjan {
    struct mutex_cond {
        int v1; bool cond1;
        int v2; bool cond2;
        mutex_cond(int v1, bool cond1, int v2, bool cond2) : v1(v1), cond1(cond1), v2(v2), cond2(cond2) {}
    };
    struct inclusive_cond {
        int v1; bool cond1;
        int v2; bool cond2;
        inclusive_cond(int v1, bool cond1, int v2, bool cond2) : v1(v1), cond1(cond1), v2(v2), cond2(cond2) {}
    };
    // Returns the mapping between vertices and their affiliated sccs.
    vector<int> scc(const vector<vector<int>>& ch) {
        int n = ch.size();
        int cnt = 0, scn = 0;
        vector<int> dfn(n), low(n), vis(n), st;
        vector<int> br(n);
        auto tarjan = [&] (auto tarjan, int v) -> void {
            dfn[v]=low[v]=++cnt;
            st.push_back(v);
            vis[v]=1;
            for(const auto&u:ch[v])
                if(!dfn[u]) tarjan(tarjan, u),low[v]=min(low[v],low[u]);
                else if(vis[u])low[v]=min(low[v],dfn[u]);
            if(dfn[v]==low[v]){
                ++scn;
                int u;
                do u=st.back(), st.pop_back(),vis[u]=0,br[u]=scn; while(u!=v);
            }
        };
        for (int i = 0; i < n; ++i) {
            if (!dfn[i]) {
                tarjan(tarjan, i);
            }
        }
        return br;
    }
    // This method can eliminate redundant edges or self-loops
    vector<vector<int>> build_scc(const vector<vector<int>>& ch) {
        int n = ch.size();
        auto br = scc(ch);
        int cnt = *max_element(br.begin(), br.end());
        vector<unordered_set<int, safe_hash>> rb(cnt + 1);
        for (int i = 0; i < n; ++i) {
            for (auto&& u : ch[i]) {
                if (br[i] != br[u]) rb[br[i]].emplace(br[u]);
            }
        }
        vector<vector<int>> res(cnt + 1);
        for (int i = 1; i <= cnt; ++i) {
            res[i] = vector<int>(rb[i].begin(), rb[i].end());
        }
        return res;
    }
    
    // This method can eliminate redundant edges or self-loops
    // return form: (scc size, children of scc)
    vector<pair<size_t, vector<int>>> build_scc_with_size(const vector<vector<int>>& ch) {
        int n = ch.size();
        auto br = scc(ch);
        int cnt = *max_element(br.begin(), br.end());
        vector<unordered_set<int, safe_hash>> rb(cnt + 1);
        for (int i = 0; i < n; ++i) {
            for (auto&& u : ch[i]) {
                if (br[i] != br[u]) rb[br[i]].emplace(br[u]);
            }
        }
        vector<pair<size_t, vector<int>>> res(cnt + 1);
        for (int i = 1; i <= cnt; ++i) {
            res[i].second = vector<int>(rb[i].begin(), rb[i].end());
        }
        for (int i = 1; i <= n; ++i) {
            res[br[i]].first += 1;
        }
        return res;
    }
    // indices start from 1, result has `n` items
    optional<vector<bool>> solve_twosat(int n, const vector<mutex_cond>& conditions) {
        vector<vector<int>> ch(2 * n + 1);
        for (auto&& [v1, cond1, v2, cond2] : conditions) {
            ch[(1 ^ cond1) * n + v1].emplace_back(cond2 * n + v2);
            ch[(1 ^ cond2) * n + v2].emplace_back(cond1 * n + v1);
        }
        auto sccno = scc(ch);
        for (int i = 1; i <= n; ++i) {
            if (sccno[i] == sccno[i + n]) {
                return nullopt;
            }
        }
        vector<bool> res;
        for (int i = 1; i <= n; ++i) {
            if (sccno[i] < sccno[i + n]) {
                res.emplace_back(false);
            } else {
                res.emplace_back(true);
            }
        }
        return res;
    };
    // indices start from 1, result has `n` items
    optional<vector<bool>> solve_twosat(int n, const vector<inclusive_cond>& conditions) {
        vector<mutex_cond> trans_conds;
        for (auto&& [v1, cond1, v2, cond2] : conditions) {
            trans_conds.emplace_back(v1, cond1, v2, not cond2);
        }
        return solve_twosat(n, trans_conds);
    }
}

namespace tarjan {
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

    vector<vector<int>> build_scc(const vector<vector<int>>& ch) {
        int n = ch.size();
        auto br = scc(ch);
        int cnt = *max_element(br.begin(), br.end());
        vector<unordered_set<int, safe_hash>> rb(cnt + 1);
        for (int i = 0; i < n; ++i) {
            for (auto&& u : ch[i]) {
                rb[br[i]].emplace(br[u]);
            }
        }
        vector<vector<int>> res(cnt + 1);
        for (int i = 1; i <= cnt; ++i) {
            res[i] = vector<int>(rb[i].begin(), rb[i].end());
        }
        return res;
    }
    
    vector<pair<size_t, vector<int>>> build_scc_with_size(const vector<vector<int>>& ch) {
        int n = ch.size();
        auto br = scc(ch);
        int cnt = *max_element(br.begin(), br.end());
        vector<unordered_set<int, safe_hash>> rb(cnt + 1);
        for (int i = 0; i < n; ++i) {
            for (auto&& u : ch[i]) {
                rb[br[i]].emplace(br[u]);
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
}

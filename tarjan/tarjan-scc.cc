// st = stack, vis = visited, br = branch(result)

constexpr int MAXN=1e5+10;
int dfn[MAXN],low[MAXN],st[MAXN],vis[MAXN],br[MAXN];
int n,cnt,stn,scn;
vector<int>ch[MAXN];
void tarjan(int v){
    dfn[v]=low[v]=++cnt;
    st[stn++]=v;
    vis[v]=1;
    for(const auto&u:ch[v])
        if(!dfn[u])tarjan(u),low[v]=min(low[v],low[u]);
        else if(vis[u])low[v]=min(low[v],dfn[u]);
    if(dfn[v]==low[v]){
        ++scn;
        int u;
        do u=st[--stn],vis[u]=0,br[u]=scn; while(u!=v);
    }
}

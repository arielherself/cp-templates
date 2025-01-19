void tarjan(int u, int father) {
  vis[u] = true;
  low[u] = dfn[u] = ++cnt;
  int child = 0;
  for (auto v : edge[u]) { 
	if (!vis[v]) {
	  child++;
	  tarjan(v, u);
	  low[u] = min(low[u], low[v]);
	  if (father != u && low[v] >= dfn[u] && !flag[u]) {
		flag[u] = true;
		res++;
	  }
	} else if (v != father) low[u] = min(low[u], dfn[v]);
  }
  if (father == u && child >= 2 && !flag[u]) {
	flag[u] = true;
	res++;
  }
}

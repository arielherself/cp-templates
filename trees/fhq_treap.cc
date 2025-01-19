// @link https://www.acwing.com/file_system/file/content/whole/index/content/8807719/
// Index starts from 1

#include <bits/stdc++.h>
using namespace std;
#define lson fhq[u].l
#define rson fhq[u].r

const int N = 1e6 + 10;

struct Node {
	int l, r;
	int val, key, size;
} fhq[N];
int cnt, root;

void pushup(int u) {
	fhq[u].size = fhq[lson].size + fhq[rson].size + 1;
}

int node(int val) {
	fhq[++cnt].val = val;
	fhq[cnt].key = rand();
	fhq[cnt].size = 1;
	return cnt;
}

void split(int u, int val, int &x, int &y) {
	if (!u) x = y = 0;
	else {
		if (fhq[u].val <= val) x = u, split(rson, val, rson, y);
		else y = u, split(lson, val, x, lson);
		pushup(u);
	}
}

int merge(int x, int y) {
	if (!x || !y) return x + y;
	if (fhq[x].key <= fhq[y].key) {
		fhq[x].r = merge(fhq[x].r, y);
		pushup(x);
		return x;
	} else {
		fhq[y].l = merge(x, fhq[y].l);
		pushup(y);
		return y;
	}
}

int x, y, z;

void insert(int val) {
	split(root, val, x, y);
	root = merge(merge(x, node(val)), y);
}

void del(int val) {
	split(root, val, x, z);
	split(x, val - 1, x, y);
	y = merge(fhq[y].l, fhq[y].r);
	root = merge(merge(x, y), z);
}

int askRank(int val) {
	split(root, val - 1, x, y);
	int res = fhq[x].size + 1;
	root = merge(x, y);
	return res;
}

int askNum(int u, int rank) {
	if (fhq[lson].size + 1 == rank) return fhq[u].val;
	if (fhq[lson].size >= rank) return askNum(lson, rank);
	else return askNum(rson, rank - fhq[lson].size - 1);
}

int askPre(int val) {
	split(root, val - 1, x, y);
	int u = x;
	while (rson) u = rson;
	root = merge(x, y);
	return fhq[u].val;
}

int askNxt(int val) {
	split(root, val, x, y);
	int u = y;
	while (lson) u = lson;
	root = merge(x, y);
	return fhq[u].val;
}

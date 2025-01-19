#include <bits/stdc++.h>
using namespace std;

int preorder[1010];
int inorder[1010];
int n;

struct TreeNode {
	int val;
	TreeNode *lc;
	TreeNode *rc;
	TreeNode(int v) : val(v) {}
	TreeNode(int v, TreeNode *l, TreeNode *r) : val(v), lc(l), rc(r) {}
};

TreeNode* dfs(int p_begin, int p_end, int i_begin, int i_end) {
	if (i_begin >= i_end) {
		return nullptr;
	}
	auto i_mid = find(inorder + i_begin, inorder + i_end, preorder[p_begin]) - inorder;
	int left_sz = i_mid - i_begin;
	TreeNode* res = new TreeNode(preorder[p_begin]);
	res->lc = dfs(p_begin + 1, p_begin + 1 + left_sz, i_begin, i_mid);
	res->rc = dfs(p_begin + 1 + left_sz, p_end, i_mid + 1, i_end);
	return res;
}

void print_postorder(TreeNode *node) {
	if (!node) {
		return;
	}
	print_postorder(node->lc);
	print_postorder(node->rc);
	cout << node->val << ' ';
}

int main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> preorder[i];
	}
	for (int i = 0; i < n; ++i) {
		cin >> inorder[i];
	}
	print_postorder(dfs(0, n, 0, n));
	return 0;
}

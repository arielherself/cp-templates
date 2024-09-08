template<typename _Tp, typename _Op = function<_Tp(const _Tp&, const _Tp&)>> struct sparse_table_2d {
    _Op op;
    vector<vector<vector<vector<_Tp>>>> st;
    sparse_table_2d(const vector<vector<_Tp>>& a, _Op&& __operation) {
        op = __operation;
        int n = a.size();
        int m = int(log2(n) + 1);
        st = vector(n, vector(n, vector(m, vector<_Tp>(m))));
        for (int k = 0; k < m; ++k) {
            for (int l = 0; l < m; ++l) {
                for (int i = 0; i + (1 << k) <= n; ++i) {
                    for (int j = 0; j + (1 << l) <= n; ++j) {
                        if (k == 0) {
                            if (l == 0) {
                                st[i][j][k][l] = a[i][j];
                            } else {
                                st[i][j][k][l] = op(st[i][j][k][l - 1], st[i][j + (1 << l - 1)][k][l - 1]);
                            }
                        } else {
                            st[i][j][k][l] = op(st[i][j][k - 1][l], st[i + (1 << k - 1)][j][k - 1][l]);
                        }
                    }
                }
            }
        }
    }
    _Tp query(size_t x1, size_t y1, size_t x2, size_t y2) {
        int s1 = lg2(x2 - x1 + 1);
        int s2 = lg2(y2 - y1 + 1);
        return op(st[x1][y1][s1][s2], op(st[x2 - (1 << s1) + 1][y1][s1][s2], op(st[x1][y2 - (1 << s2) + 1][s1][s2], st[x2 - (1 << s1) + 1][y2 - (1 << s2) + 1][s1][s2])));
    }
};

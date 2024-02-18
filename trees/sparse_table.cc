template<typename _Tp, typename _Op = function<_Tp(const _Tp&, const _Tp&)>> struct sparse_table {
    _Op op;
    vector<vector<_Tp>> st;
    template <typename ReverseIterator>
    sparse_table(ReverseIterator __first, ReverseIterator __last, _Op&& __operation) {
        op = __operation;
        int n = distance(__first, __last);
        st = vector<vector<_Tp>>(n, vector<_Tp>(int(log2(n) + 1)));
        int i = n - 1;
        for (auto it = __first; it != __last; ++it) {
            st[i][0] = *it;
            for (int j = 1; i + (1 << j) <= n; ++j) {
                st[i][j] = op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
            i -= 1;
        }
    }
    _Tp query(size_t __start, size_t __end) {
        int s = log2(__end - __start + 1);
        return op(st[__start][s], st[__end - (1 << s) + 1][s]);
    }
};

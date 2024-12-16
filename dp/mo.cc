template <typename record_t>
vector<typename record_t::return_t> mo(record_t& solver, const vector<pii>& queries, int n) {
    int m = queries.size();
    int block = sqrt(ld(n));
    vector<int> idx(m);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&] (int i, int j) {
        auto&& lhs = queries[i];
        auto&& rhs = queries[j];
        if (lhs.first / block != rhs.first / block) {
            return lhs.first < rhs.first;
        }
        if (lhs.first / block % 2) {
            return lhs.second < rhs.second;
        }
        return lhs.second > rhs.second;
    });
    vector<typename record_t::return_t> res(m);
    for (auto&& i : idx) {
        auto&& [tl, tr] = queries[i];
        while (solver.l > tl) solver.movell();
        while (solver.r < tr) solver.moverr();
        while (solver.l < tl) solver.movelr();
        while (solver.r > tr) solver.moverl();
        res[i] = solver.get();
    }
    return res;
}

struct {
    using return_t = int;
    int l = 0, r = 0;
    return_t res = 0;
    return_t get(void) const {
        return res;
    }
    void movell(void) {
    }
    void movelr(void) {
    }
    void moverr(void) {
    }
    void moverl(void) {
    }
} solver;

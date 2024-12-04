template <typename T, typename IndexType = ll>
struct ODT {
    struct Info {
        IndexType l, r;
        mutable T val;
        Info(const IndexType& l, const IndexType& r, const T& val) : l(l), r(r), val(val) {}
        friend inline bool operator<(const Info& lhs, const Info& rhs) { return lhs.l < rhs.l; }
    };

    set<Info> info;

    ODT() = delete;
    ODT(const IndexType& left, const IndexType& right, const T& val) : info {{ left, right, val }} {}

    typename set<Info>::iterator split(const IndexType& x) {
        auto it = info.lower_bound({ x, {}, {} });
        if (it != info.end() and it->l == x) {
            return it;
        }
        --it;
        auto [l, r, val] = *it;
        info.erase(it);
        info.emplace(l, x - 1, val);
        return info.emplace(x, r, val).first;
    }

    void assign(const IndexType& l, const IndexType& r, const T& val) {
        auto ri = split(r + 1), li = split(l);
        info.erase(li, ri);
        info.emplace(l, r, val);
    }

    void transform(const IndexType& l, const IndexType& r, const function<T(const Info&)>& operation) {
        auto ri = split(r + 1), li = split(l);
        for (; li != ri; ++li) {
            li->val = operation(*li);
        }
    }

    template <typename U>
    U accumulate(const IndexType& l, const IndexType& r, U&& init, const function<U(const U&, const Info&)>& operation = std::plus()) {
        auto ri = split(r + 1), li = split(l);
        U res = init;
        for (; li != ri; ++li) {
            res = operation(res, *li);
        }
        return res;
    }
};

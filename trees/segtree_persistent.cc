template <typename Addable_Info> struct segtree {
    using info_type = Addable_Info;
    using size_type = size_t;
    struct Node {
        size_type lson, rson;
        info_type info;
    };
    vector<Node> d;
    vector<size_type> version_root;
    size_type _max;
    void _copy(size_type& virt) {
        int o = virt;
        virt = d.size();
        d.emplace_back();
        if (o != 0) d.back() = d[o];
    }
    explicit segtree(size_type&& _max) : d(1), _max(_max - 1) {
        version_root.emplace_back(0);
    }
    segtree(const vector<info_type>& init) : d(1), _max(init.size() - 1) {
        version_root.emplace_back(0);
        auto dfs = [&] (auto dfs, size_type s, size_type t, size_type p) -> void {
            if (s == t) {
                d[p].info = init[s];
                return;
            }
            int m = s + t >> 1;
            _copy(d[p].lson), _copy(d[p].rson);
            dfs(dfs, s, m, d[p].lson);
            dfs(dfs, m + 1, t, d[p].rson);
        };
        dfs(dfs, 0, _max, version_root[0]);
    }
    void _set(size_type s, size_type t, size_type p, size_type x, const info_type& c) {
        if (s == t) {
            d[p].info = c;
            return;
        }
        size_type m = s + (t - s >> 1);
        if (x <= m) {
            _copy(d[p].lson);
            _set(s, m, d[p].lson, x, c);
        } else {
            _copy(d[p].rson);
            _set(m + 1, t, d[p].rson, x, c);
        }
        d[p].info = d[d[p].lson].info + d[d[p].rson].info;
    }
    size_type _clone(size_type version) {
        d.emplace_back(d[version_root[version]]);
        version_root.emplace_back(d.size() - 1);
        return version_root.size() - 1;
    }
    size_type set(size_type version, size_type loc, const info_type& c) {
        size_type new_version = _clone(version);
        _set(0, _max, version_root[new_version], loc, c);
        return new_version;
    }
    info_type _range_query(size_type s, size_type t, size_type p, size_type l, size_type r) {
        if (l <= s and t <= r) {
            return d[p].info;
        }
        size_type m = s + (t - s >> 1);
        info_type ret = {};
        if (l <= m and d[p].lson != 0) {
            ret = ret + _range_query(s, m, d[p].lson, l, r);
        }
        if (r > m and d[p].rson != 0) {
            ret = ret + _range_query(m + 1, t, d[p].rson, l, r);
        }
        return ret;
    }
    info_type range_query(size_type version, size_type l, size_type r) {
        return _range_query(0, _max, version_root[version], l, r);
    }
    info_type query(size_type version, size_type loc) {
        return range_query(version, loc, loc);
    }
};
struct Info {
    int val = INF;
};
Info operator+(const Info& lhs, const Info& rhs) {
    return { min(lhs.val, rhs.val) };
}

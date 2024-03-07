template<typename Addable_Info_t, typename Tag_t, typename Sequence = std::vector<Addable_Info_t>> class segtree {
private:
    using size_type = uint64_t;
    using info_type = Addable_Info_t;
    using tag_type = Tag_t;
    size_type _max;
    vector<info_type> d;
    vector<tag_type> b;

    void push(size_type p) {
        d[p * 2].apply(b[p]), d[p * 2 + 1].apply(b[p]);
        b[p * 2].apply(b[p]), b[p * 2 + 1].apply(b[p]);
        b[p] = tag_type();
    }
    void set(size_type s, size_type t, size_type p, size_type x, const info_type& c) {
        if (s == t) {
            d[p] = c;
            return;
        }
        size_type m = s + (t - s >> 1);
        if (s != t) push(p);
        if (x <= m) range_set(s, m, p * 2, x, c);
        else  range_set(m + 1, t, p * 2 + 1, x, c);
        d[p] = d[p * 2] + d[p * 2 + 1];
    }
    
    void range_apply(size_type s, size_type t, size_type p, size_type l, size_type r, const tag_type& c) {
        if (l <= s && t <= r) {
            d[p].apply(c);
            b[p].apply(c);
            return;
        }
        size_type m = s + (t - s >> 1);
        push(p);
        if (l <= m) range_apply(s, m, p * 2, l, r, c);
        if (r > m)  range_apply(m + 1, t, p * 2 + 1, l, r, c);
        d[p] = d[p * 2] + d[p * 2 + 1];
    }

    info_type range_query(size_type s, size_type t, size_type p, size_type l, size_type r) {
        if (l <= s && t <= r) {
            return d[p];
        }
        size_type m = s + (t - s >> 1);
        info_type res = {};
        push(p);
        if (l <= m) res = res + range_query(s, m, p * 2, l, r);
        if (r > m)  res = res + range_query(m + 1, t, p * 2 + 1, l, r);
        return res;
    }

    void build(const Sequence& a, size_type s, size_type t, size_type p) {
        if (s == t) {
            d[p] = a[s];
            return;
        }
        int m = s + (t - s >> 1);
        build(a, s, m, p * 2);
        build(a, m + 1, t, p * 2 + 1);
        d[p] = d[p * 2] + d[p * 2 + 1];
    }
public:
    segtree(size_type __max) : d(4 * __max), b(4 * __max), _max(__max - 1) {}
    segtree(const Sequence& a) : segtree(a.size()) {
        build(a, {}, _max, 1);
    }

    void set(size_type i, const info_type& c) {
        set({}, _max, 1, i, c);
    }
    
    void range_apply(size_type l, size_type r, const tag_type& c) {
        range_apply({}, _max, 1, l, r, c);
    }

    void apply(size_type i, const tag_type& c) {
        range_apply(i, i, c);
    }

    info_type range_query(size_type l, size_type r) {
        return range_query({}, _max, 1, l, r);
    }

    info_type query(size_type i) {
        return range_query(i, i);
    }

    Sequence serialize() {
        Sequence res = {};
        for (size_type i = 0; i <= _max; ++i) {
            res.push_back(query(i));
        }
        return res;
    }

    const vector<info_type> get_d() {
        return d;
    }
};

struct Set_Tag {
    int val = -1;
    void apply(const Set_Tag& rhs) {
        if (rhs.val != -1)
        val = rhs.val;
    }
};

struct Set_Info {
    int val = 0;
    void apply(const Set_Tag& rhs) {
        if (rhs.val != -1)
        val = rhs.val;
    }
};

Set_Info operator+(const Set_Info &a, const Set_Info &b) {
    return {a.val + b.val};
}

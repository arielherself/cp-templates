// @link https://www.acwing.com/file_system/file/content/whole/index/content/8807719/
// Everything starts from 1

template <typename T> class treap {

#define lson fhq[u].l
#define rson fhq[u].r

private:
    using size_type = size_t;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const reference;

    struct Node {
        int key;
        size_type l, r, size;
        value_type val;
    };
    vector<Node> fhq;
    size_type cnt, root;
    size_type x, y, z;
    size_type _size;

    void pushup(size_type u) {
        fhq[u].size = fhq[lson].size + fhq[rson].size + 1;
    }

    size_type node(value_type val) {
        if (cnt + 1 >= fhq.size()) {
            fhq.push_back({});
        }
        fhq[++cnt].val = val;
        fhq[cnt].key = rand();
        fhq[cnt].size = 1;
        return cnt;
    }

    void split(size_type u, value_type val, size_type &x, size_type &y) {
        if (!u) x = y = 0;
        else {
            if (fhq[u].val <= val) x = u, split(rson, val, rson, y);
            else y = u, split(lson, val, x, lson);
            pushup(u);
        }
    }

    size_type merge(size_type x, size_type y) {
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

    value_type askNum(size_type u, size_type rank) {
        if (fhq[lson].size + 1 == rank) return fhq[u].val;
        if (fhq[lson].size >= rank) return askNum(lson, rank);
        else return askNum(rson, rank - fhq[lson].size - 1);
    }

public:
    treap() : fhq(1), cnt(0), root(0), _size(0) {}
    explicit treap(size_type n) : fhq(1), cnt(0), root(0), _size(0) {
        fhq.reserve(n + 1);
    }

    template<typename _InputIterator,
             typename = std::_RequireInputIter<_InputIterator>>
        treap(_InputIterator __first, _InputIterator __last)
        : fhq(1), cnt(0), root(0), _size(0) {
            __try {
                for (; __first != __last; ++__first) {
                    insert(*__first);
                }
            } __catch(...) {
                clear();
                __throw_exception_again;
            }
    }

    void clear() {
        _size = root = cnt = 0;
        fill(fhq.begin(), fhq.end(), {});
    }

    void insert(value_type val) {
        assert(!contains(val));
        ++_size;
        split(root, val, x, y);
        root = merge(merge(x, node(val)), y);
    }

    void remove(value_type val) {
        assert(contains(val));
        --_size;
        split(root, val, x, z);
        split(x, val - 1, x, y);
        y = merge(fhq[y].l, fhq[y].r);
        root = merge(merge(x, y), z);
    }

    size_type index_of(value_type val) {
        split(root, val - 1, x, y);
        size_type res = fhq[x].size + 1;
        root = merge(x, y);
        return res;
    }

    value_type at(size_type rank) {
        assert(rank > 0 && rank <= _size);
        return askNum(root, rank);
    }

    value_type prev_element(value_type val) {
        split(root, val - 1, x, y);
        size_type u = x;
        while (rson) u = rson;
        root = merge(x, y);
        return fhq[u].val;
    }

    value_type next_element(value_type val) {
        split(root, val, x, y);
        size_type u = y;
        while (lson) u = lson;
        root = merge(x, y);
        return fhq[u].val;
    }

    bool contains(value_type val) {
        size_type idx = index_of(val);
        return idx <= _size && at(idx) == val;
    }

    size_type size() {
        return _size;
    }

#undef lson
#undef rson
};

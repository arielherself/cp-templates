/*
 * A vector-like structure that supports:
 * 	1. Random access;
 * 	2. Random insert;
 * 	3. Random remove;
 * 	4. Random modification;
 * 	5. Range query.
 * All operations are of O(log n) time complexity.
 */
template <typename Monoid>
struct DynamicVector {
	struct Node {
		ull key;
		size_t size;
		Monoid info;
		Monoid subtree_info;
		optional<size_t> lson;
		optional<size_t> rson;
	};
	vector<Node> node;
	optional<size_t> root;

	DynamicVector() = default;

	always_inline size_t newnode(const Monoid& info) {
		node.push_back({
				.key = rd(),
				.size = 1,
				.info = info,
				.subtree_info = info,
				.lson = nullopt,
				.rson = nullopt,
				});
		return node.size() - 1;
	}

	always_inline size_t get_size(optional<size_t> v) {
		return v ? node[*v].size : 0;
	}

	always_inline void pull(size_t v) {
		node[v].size = get_size(node[v].lson) + get_size(node[v].rson) + 1;
		if (node[v].lson) {
			node[v].subtree_info = node[*node[v].lson].subtree_info + node[v].info;
		} else {
			node[v].subtree_info = node[v].info;
		}
		if (node[v].rson) {
			node[v].subtree_info = node[v].subtree_info + node[*node[v].rson].subtree_info;
		}
	}

	optional<size_t> merge(optional<size_t> u, optional<size_t> v) {
		if (not u and not v) return nullopt;
		if (u and not v) return u;
		if (not u and v) return v;

		if (node[*u].key < node[*v].key) {
			node[*u].rson = merge(node[*u].rson, v);
			pull(*u);
			return u;
		} else {
			node[*v].lson = merge(u, node[*v].lson);
			pull(*v);
			return v;
		}
	}

	void split(optional<size_t> v, size_t rk, optional<size_t>& l, optional<size_t>& r) {
		if (not v) {
			l = nullopt;
			r = nullopt;
			return;
		}

		size_t left = get_size(node[*v].lson) + 1;

		if (rk >= left) {
			l = v;
			split(node[*v].rson, rk - left, node[*v].rson, r);
		} else {
			r = v;
			split(node[*v].lson, rk, l, node[*v].lson);
		}
		pull(*v);
	}

	always_inline size_t size(void) {
		return root ? node[*root].size : 0;
	}

	always_inline void insert(size_t pos, const Monoid& value) {
		optional<size_t> left, right;
		split(root, pos, left, right);
		root = newnode(value);
		root = merge(left, root);
		root = merge(root, right);
	}

	always_inline Monoid erase(size_t pos) {
		optional<size_t> left, mid, right;
		split(root, pos + 1, left, right);
		split(left, pos, left, mid);
		Monoid ret = node[*mid].info;
		root = merge(left, right);
		return ret;
	}

	always_inline Monoid& operator[](size_t pos) {
		optional<size_t> left, mid, right;
		split(root, pos + 1, left, right);
		split(left, pos, left, mid);
		Monoid& ret = node[*mid].info;
		root = merge(left, mid);
		root = merge(root, right);
		return ret;
	}

	always_inline void push_back(const Monoid& value) {
		insert(size(), value);
	}

	always_inline Monoid pop_back(void) {
		return erase(size() - 1);
	}

	always_inline Monoid& back(void) {
		return (*this)[size() - 1];
	}

	always_inline void push_front(const Monoid& value) {
		insert(0, value);
	}

	always_inline Monoid pop_front(void) {
		return erase(0);
	}

	always_inline Monoid& front(void) {
		return (*this)[0];
	}

	always_inline Monoid range(size_t l, size_t r) {
		optional<size_t> left, mid, right;
		split(root, r + 1, left, right);
		split(left, l, left, mid);
		Monoid ret = node[*mid].subtree_info;
		root = merge(left, mid);
		root = merge(root, right);
		return ret;
	}

	always_inline Monoid& at(size_t pos) {
		size_t sz = size();
		if (pos >= sz)
			__throw_out_of_range_fmt(__N("DynamicVector::at: pos "
						"(which is %zu) >= size() "
						"(which is %zu)"),
					pos, sz);
		return (*this)[pos];
	}

	template <typename Pred>
		size_t binary_search(optional<size_t> v, Pred pred) {
			if (not v) {
				return 0;
			}
			if (pred(node[*v].info) == true) {
				return binary_search(node[*v].lson, pred);
			} else {
				return get_size(node[*v].lson) + 1 + binary_search(node[*v].rson, pred);
			}
		}

	/// Find the first element from left that pred(x) is true.
	template <typename Pred>
		always_inline size_t binary_search(Pred pred) {
			return binary_search(root, pred);
		}

	template <typename Pred>
		size_t prefix_binary_search(optional<size_t> v, Pred pred) {
			if (not v) {
				return 1;
			}
			Monoid curr = node[*v].info;
			if (node[*v].lson) {
				curr = node[*node[*v].lson].subtree_info + curr;
			}
			if (pred(curr) == true) {
				return prefix_binary_search(node[*v].lson, pred);
			} else {
				return get_size(node[*v].lson) + 1 + prefix_binary_search(node[*v].rson, pred);
			}
		}

	/// Find the first position from left that pred([0 .. x]) is true.
	template <typename Pred>
		always_inline size_t prefix_binary_search(Pred pred) {
			return prefix_binary_search(root, pred);
		}

	template <typename Pred>
		size_t suffix_binary_search(optional<size_t> v, Pred pred) {
			if (not v) {
				return 1;
			}
			Monoid curr = node[*v].info;
			if (node[*v].rson) {
				curr = curr + node[*node[*v].rson].subtree_info;
			}
			if (pred(curr) == true) {
				return suffix_binary_search(node[*v].rson, pred);
			} else {
				return get_size(node[*v].rson) + 1 + suffix_binary_search(node[*v].lson, pred);
			}
		}

	/// Find the first position from right that pred([x - 1 .. n - 1]) is true.
	template <typename Pred>
		always_inline size_t suffix_binary_search(Pred pred) {
			return size() + 1 - suffix_binary_search(root, pred);
		}

	/// Find the first element from left that comp(x, value) is false.
	template <typename Compare>
		always_inline size_t lower_bound(const Monoid& value, Compare comp) {
			return binary_search(expr(comp(x, value) == false, auto&& x));
		}

	/// Find the first element from left that is not less than value.
	always_inline size_t lower_bound(const Monoid& value) {
		return lower_bound(value, std::less<Monoid>());
	}

	// Find the first element from left that comp(x, value) is true.
	template <typename Compare>
		always_inline size_t upper_bound(const Monoid& value, Compare comp) {
			return binary_search(expr(comp(x, value) == true, auto&& x));
		}

	/// Find the first element from left that is greater than value.
	always_inline size_t upper_bound(const Monoid& value) {
		return upper_bound(value, std::greater<Monoid>());
	}

	// TODO: lazy tag
};

struct Info {
	int val = INF;
	int id = 0;
};

always_inline Info operator+(const Info& a, const Info& b) {
	return {
		.val = max(a.val, b.val),
		.id = a.val > b.val ? a.id : b.id,
	};
}


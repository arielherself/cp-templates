// Set intersection supporting std::unordered_set.
template <typename Set, typename Key = typename Set::value_type>
static inline Set set_intersection(const Set& lhs, const Set& rhs) {
	if (lhs.size() <= rhs.size()) {
		Set iset;
		for (const Key& key : lhs) {
			if (rhs.count(key) > 0) {
				iset.insert(key);
			}
		}
		return std::move(iset);
	} else {
		return set_intersection(rhs, lhs);
	}
}

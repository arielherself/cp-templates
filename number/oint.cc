template <typename T, T MDL, T MAX = INT_MAX>
struct oint {
	static_assert(MDL > MAX, "Number will never overflow because modulus is too small");
	bool carry;
	T val;
	oint() : carry(0), val(0) {}
	oint(const T& v) : carry(v > MAX), val(v % MDL) {}
	oint(const bool& carry, const T& val) : carry(carry), val(val) {}
	friend oint operator*(const oint& a, const oint& b) {
		return {
			a.carry or b.carry or a.val > MAX / b.val,
			(a.val * b.val) % MDL,
		};
	}
	friend oint operator+(const oint& a, const oint& b) {
		return {
			a.carry or b.carry or a.val > MAX - b.val,
			(a.val + b.val) % MDL,
		};
	}
	oint& operator+=(const oint& rhs) { return *this = *this + rhs; }
	oint& operator*=(const oint& rhs) { return *this = *this * rhs; }
};

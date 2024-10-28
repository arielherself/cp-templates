template <typename T, T MDL, T MAX = INT_MAX>
struct oint {
    static_assert(MDL > MAX, "Number will never overflow because modulus is too small");
    bool carry;
    T val;
    oint() : carry(0), val(0) {}
    oint(const T& v) : carry(v > MAX), val(v % MDL) {}
    friend oint operator*(const oint& a, const oint& b) {
        oint res;
        res.carry = a.carry | b.carry;
        if (not res.carry and a.val > MAX / b.val) {
            res.carry = 1;
        }
        res.val = (a.val * b.val) % MDL;
        return res;
    }
    friend oint operator+(const oint& a, const oint& b) {
        oint res;
        res.carry = a.carry | b.carry;
        if (not res.carry and a.val > MAX - b.val) {
            res.carry = 1;
        }
        res.val = (a.val + b.val) % MDL;
        return res;
    }
    oint& operator+=(const oint& rhs) { return *this = *this + rhs; }
    oint& operator*=(const oint& rhs) { return *this = *this * rhs; }
};

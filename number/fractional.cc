template<typename T>
struct fractional {
    T p, q;
    inline void reduce(void) {
        if (q < 0) p = -p, q = -q;
        if (p == 0) q = 1; else { T g = mygcd(p, q); p /= g; q /= g; }
    }
    fractional(void) : p(0), q(1) {}
    template <typename U>
    fractional(const U& p) : p(p), q(1) { reduce(); }
    fractional(const T& p, const T& q) : p(p), q(q) { reduce(); }
    inline friend fractional operator+(const fractional& lhs) { return *lhs; }
    inline friend fractional operator-(const fractional& lhs) { return { -lhs.p, lhs.q }; }
    inline friend fractional operator+(const fractional& lhs, const fractional& rhs) { return { lhs.p * rhs.q + lhs.q * rhs.p, lhs.q * rhs.q }; }
    inline friend fractional operator-(const fractional& lhs, const fractional& rhs) { return lhs + (-rhs); }
    inline friend fractional operator*(const fractional& lhs, const fractional& rhs) { return { lhs.p * rhs.p, lhs.q * rhs.q }; }
    inline friend fractional operator/(const fractional& lhs, const fractional& rhs) { return lhs * fractional(rhs.q, rhs.p); }
    inline fractional& operator+=(const fractional& rhs) { return *this = *this + rhs; }
    inline fractional& operator-=(const fractional& rhs) { return *this = *this - rhs; }
    inline fractional& operator*=(const fractional& rhs) { return *this = *this * rhs; }
    inline fractional& operator/=(const fractional& rhs) { return *this = *this / rhs; }
    inline friend bool operator==(const fractional& lhs, const fractional& rhs) { return lhs.p == rhs.p and lhs.q == rhs.q; }
    inline friend bool operator!=(const fractional& lhs, const fractional& rhs) { return not (lhs == rhs); }
    inline friend bool operator<(const fractional& lhs, const fractional& rhs) { return (lhs - rhs).p < 0; }
    inline friend bool operator>=(const fractional& lhs, const fractional& rhs) { return not (lhs < rhs); }
    inline friend bool operator>(const fractional& lhs, const fractional& rhs) { return lhs >= rhs and lhs != rhs; }
    inline friend bool operator<=(const fractional& lhs, const fractional& rhs) { return lhs < rhs or lhs == rhs; }
};

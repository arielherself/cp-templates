template <typename T>
inline T mygcd(T a, T b) { return b == 0 ? a : mygcd(b, a % b); }

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
    inline fractional operator+(void) const { return *this; }
    inline fractional operator-(void) const { return { -p, q }; }
    inline fractional operator+(const fractional& rhs) const { return { p * rhs.q + q * rhs.p, q * rhs.q }; }
    inline fractional operator-(const fractional& rhs) const { return *this + (-rhs); }
    inline fractional operator*(const fractional& rhs) const { return { p * rhs.p, q * rhs.q }; }
    inline fractional operator/(const fractional& rhs) const { return *this * fractional(rhs.q, rhs.p); }
    inline fractional& operator+=(const fractional& rhs) { return *this = *this + rhs; }
    inline fractional& operator-=(const fractional& rhs) { return *this = *this - rhs; }
    inline fractional& operator*=(const fractional& rhs) { return *this = *this * rhs; }
    inline fractional& operator/=(const fractional& rhs) { return *this = *this / rhs; }
    inline bool operator==(const fractional& rhs) const { return p == rhs.p and q == rhs.q; }
    inline bool operator!=(const fractional& rhs) const { return not (*this == rhs); }
    inline bool operator<(const fractional& rhs) const { return (*this - rhs).p < 0; }
    inline bool operator>=(const fractional& rhs) const { return not (*this < rhs); }
    inline bool operator>(const fractional& rhs) const { return *this >= rhs and *this != rhs; }
    inline bool operator<=(const fractional& rhs) const { return *this < rhs or *this == rhs; }
};

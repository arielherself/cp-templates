template<typename T>
struct fractional {
    T p, q;
    inline void reduce(void) {
        if (q < 0) p = -p, q = -q;
        if (p == 0) q = 1; else { T g = mygcd(abs(p), abs(q)); p /= g; q /= g; }
    }
    fractional(void) : p(0), q(1) {}
    template <typename U>
    fractional(const U& p) : p(p), q(1) { reduce(); }
    fractional(const T& p, const T& q) : p(p), q(q) { reduce(); }
    friend inline fractional operator+(const fractional& lhs) { return *lhs; }
    friend inline fractional operator-(const fractional& lhs) { return { -lhs.p, lhs.q }; }
    friend inline fractional operator+(const fractional& lhs, const fractional& rhs) { return { lhs.p * rhs.q + lhs.q * rhs.p, lhs.q * rhs.q }; }
    friend inline fractional operator-(const fractional& lhs, const fractional& rhs) { return lhs + (-rhs); }
    friend inline fractional operator*(const fractional& lhs, const fractional& rhs) { return { lhs.p * rhs.p, lhs.q * rhs.q }; }
    friend inline fractional operator/(const fractional& lhs, const fractional& rhs) { return lhs * fractional(rhs.q, rhs.p); }
    inline fractional& operator+=(const fractional& rhs) { return *this = *this + rhs; }
    inline fractional& operator-=(const fractional& rhs) { return *this = *this - rhs; }
    inline fractional& operator*=(const fractional& rhs) { return *this = *this * rhs; }
    inline fractional& operator/=(const fractional& rhs) { return *this = *this / rhs; }
    friend inline bool operator==(const fractional& lhs, const fractional& rhs) { return lhs.p == rhs.p and lhs.q == rhs.q; }
    friend inline bool operator!=(const fractional& lhs, const fractional& rhs) { return not (lhs == rhs); }
    friend inline bool operator<(const fractional& lhs, const fractional& rhs) { return (lhs - rhs).p < 0; }
    friend inline bool operator>=(const fractional& lhs, const fractional& rhs) { return not (lhs < rhs); }
    friend inline bool operator>(const fractional& lhs, const fractional& rhs) { return lhs >= rhs and lhs != rhs; }
    friend inline bool operator<=(const fractional& lhs, const fractional& rhs) { return lhs < rhs or lhs == rhs; }
    friend inline ostream& operator<<(ostream& out, const fractional& x) { return out << x.p << '/' << x.q; }
    friend inline istream& operator>>(istream& in, fractional& x) {
        read(string, s);
        auto point = find(s.begin(), s.end(), '.');
        string left(s.begin(), point);
        string right(point, s.end());
        if (right.size()) right.erase(right.begin());
        T divisor = 1;
        for (auto&& _ : right) {
            divisor *= 10;
        }
        T l, r;
        stringstream(left) >> l;
        stringstream(right) >> r;
        x = l + fractional(r, divisor);
        return in;
    }
};

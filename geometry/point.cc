template <typename T> struct point {
	T x, y;
	point() : x(), y() {}
	point(const pair<T, T>& a) : x(a.first), y(a.second) {}
	point(const T& x, const T& y) : x(x), y(y) {}

	inline T square() const { return x * x + y * y; }
	inline ld norm() const { return sqrt((long double)(square())); }

	inline point operator+(const point& rhs) const { return point(x + rhs.x, y + rhs.y); }
	inline point operator-(const point& rhs) const { return point(x - rhs.x, y - rhs.y); }
	inline point operator+() const { return *this; }
	inline point operator-() const { return point(-x, -y); }
	inline point operator*(const T& a) const { return point(x * a, y * a); }
	inline T operator*(const point& rhs) const { return x * rhs.y - y * rhs.x; }
	inline point operator/(const T& a) const { return point(x / a, y / a); }
	inline point& operator+=(const point& rhs) { x += rhs.x, y += rhs.y; return *this; }
	inline point& operator-=(const point& rhs) { x -= rhs.x, y -= rhs.y; return *this; }
	inline point& operator*=(const T& a) { x *= a, y *= a; return *this; }
	inline point& operator/=(const T& a) { x /= a, y /= a; return *this; }

	inline bool operator==(const point& rhs) const { return x == rhs.x and y == rhs.y; }
	inline bool operator!=(const point& rhs) const { return not (*this == rhs); }
	inline bool operator<(const point& rhs) const { return pair(x, y) < pair(rhs.x, rhs.y); }
	inline bool operator<=(const point& rhs) const { return *this < rhs or *this == rhs; }
	inline bool operator>(const point& rhs) const { return not (*this <= rhs); }
	inline bool operator>=(const point& rhs) const { return not (*this < rhs); }

	static inline ld slope(const point& a, const point& b) {
		if (a.x == b.x) return INFLL;
		return ld(a.y - b.y) / (a.x - b.x);
	}

	// distance from point `a` to line `l--r`
	static inline ld dist(const point& a, const point& l, const point& r) {
		return area(a, l, r) * 2 / (l - r).norm();
	}

	static inline ld area(const point& a, const point& b, const point& c) {
		return (b - a) * (c - a) / ld(2);
	}

	friend inline istream& operator>>(istream& in, point& a) {
		return in >> a.x >> a.y;
	}

	friend inline ostream& operator<<(ostream& out, const point& a) {
		return out << a.x << ' ' << a.y;
	}
};

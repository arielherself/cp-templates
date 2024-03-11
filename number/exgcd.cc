namespace Exgcd {
    template <typename T> T abs(T x) { return x < 0 ? -x : x; }

    template <typename T>
    struct exgcd_solution_t {
        T x, y, gcd;
    };

    template <typename T>
    struct diophantine_solution_t {
        exgcd_solution_t<T> x_min, y_min;
        T range;
    };

    // solve `ax + by = gcd(a, b)`
    template <typename T>
    optional<exgcd_solution_t<T>> exgcd(T a, T b) {
        if (a < 0 || b < 0 || a == 0 && b == 0) return nullopt;
        T x, y, g;
        function<void(T, T)> __exgcd = [&__exgcd, &x, &y, &g] (T a, T b) -> void {
            if (b == 0) {
                g = a, x = 1, y = 0;
            } else {
                __exgcd(b, a % b);
                swap(x, y);
                y -= a / b * x;
            }
        };
        __exgcd(a, b);
        return {{ x, y, g }};
    };

    template <typename T>
    optional<T> inverse(T a, T b) {
        auto raw = exgcd(a, b);
        if (raw == nullopt || raw.value().gcd != 1) {
            return nullopt;
        } else {
            return mod(raw.value().x, b);
        }
    }

    // solve { x = a_i (mod n_i) } if n_i's are coprime
    template <typename T>
    optional<T> crt(const vector<pair<T, T>>& equations) {
        T prod = 1;
        for (auto&& [a, n] : equations) {
            prod *= n;
        }
        T res = 0;
        for (auto&& [a, n] : equations) {
            T m = prod / n;
            auto m_rev = inverse(m, n);
            if (m_rev == nullopt) return nullopt;
            res = mod(res + a * mod(m * m_rev.value(), prod), prod);
        }
        return res;
    }

    // find minimal non-negative integral solutions of `ax + by = c`. It's not guaranteed that the other variable is non-negative.
    template <typename T>
    optional<diophantine_solution_t<T>> diophantine(T a, T b, T c, bool force_positive = false) {
        if (a < 0 || b < 0 || a == 0 && b == 0) return nullopt;
        auto raw = exgcd(a, b).value();
        if (c % raw.gcd) {
            return nullopt;
        } else {
            T x = raw.x * c / raw.gcd, y = raw.y * c / raw.gcd;
            T kx = force_positive ? (x <= 0 ? (-x) * raw.gcd / b + 1 : 1 - (x + b / raw.gcd - 1) * raw.gcd / b) : (x <= 0 ? ((-x) + b / raw.gcd - 1) * raw.gcd / b : (- x * raw.gcd / b));
            T ky = force_positive ? (y <= 0 ? (- 1 - (-y) * raw.gcd / a) : (y + a / raw.gcd - 1) * raw.gcd / a - 1) : (y <= 0 ? (- ((-y) + a / raw.gcd - 1) * raw.gcd / a) : y * raw.gcd / a);
            return {{ { x + b * kx / raw.gcd , y - a * kx / raw.gcd , raw.gcd }, { x + b * ky / raw.gcd , y - a * ky / raw.gcd, raw.gcd }, abs(kx - ky) + 1 }};
        }
    }

    // find the minimal non-negative integral solution of `ax = b (mod n)`
    template <typename T>
    optional<T> congruential(T a, T b, T n) {
        if (a == 0) {
            if (b != 0) return nullopt;
            return 0;
        }
        if (a < 0 && a != LLONG_MIN && b != LLONG_MIN) a = -a, b = -b;
        auto sol = diophantine(a, n, b);
        if (sol == nullopt) {
            return nullopt;
        } else {
            return sol.value().x_min.x;
        }
    }
}

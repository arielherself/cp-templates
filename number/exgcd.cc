namespace Exgcd {
    struct exgcd_solution_t {
        ll x, y, gcd;
    };

    struct diophantine_solution_t {
        exgcd_solution_t x_min, y_min;
        ll range;
    };

    // solve `ax + by = gcd(a, b)`
    optional<exgcd_solution_t> exgcd(ll a, ll b) {
        if (a < 0 || b < 0 || a == 0 && b == 0) return nullopt;
        ll x, y, g;
        function<void(ll, ll)> __exgcd = [&__exgcd, &x, &y, &g] (ll a, ll b) -> void {
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

    optional<ll> inverse(ll a, ll b) {
        auto raw = exgcd(a, b);
        if (raw == nullopt || raw.value().gcd != 1) {
            return nullopt;
        } else {
            return mod(raw.value().x, b);
        }
    }

    // find minimal non-negative integral solutions of `ax + by = c`
    optional<diophantine_solution_t> diophantine(ll a, ll b, ll c, bool force_positive = false) {
        if (a < 0 || b < 0 || a == 0 && b == 0) return nullopt;
        auto raw = exgcd(a, b).value();
        if (c % raw.gcd) {
            return nullopt;
        } else {
            ll x = raw.x * c / raw.gcd, y = raw.y * c / raw.gcd;
            ll kx = force_positive ? (x <= 0 ? (-x) * raw.gcd / b + 1 : 1 - (x + b / raw.gcd - 1) * raw.gcd / b) : (x <= 0 ? ((-x) + b / raw.gcd - 1) * raw.gcd / b : (- x * raw.gcd / b));
            ll ky = force_positive ? (y <= 0 ? (- 1 - (-y) * raw.gcd / a) : (y + a / raw.gcd - 1) * raw.gcd / a - 1) : (y <= 0 ? (- ((-y) + a / raw.gcd - 1) * raw.gcd / a) : y * raw.gcd / a);
            return {{ { x + b * kx / raw.gcd , y - a * kx / raw.gcd , raw.gcd }, { x + b * ky / raw.gcd , y - a * ky / raw.gcd, raw.gcd }, abs(kx - ky) + 1 }};
        }
    }

    // find the minimal non-negative integral solution of `ax = b (mod n)`
    optional<ll> congruential(ll a, ll b, ll n) {
        if (a < 0 && a != LLONG_MIN && b != LLONG_MIN) a = -a, b = -b;
        auto sol = diophantine(a, n, b);
        if (sol == nullopt) {
            return nullopt;
        } else {
            return sol.value().x_min.x;
        }
    }
}

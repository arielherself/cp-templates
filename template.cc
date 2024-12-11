// #pragma GCC target("popcnt,lzcnt,abm,bmi,bmi2")
#pragma GCC optimize("Ofast,unroll-loops")
/************* This code requires C++17. ***************/

#include<bits/stdc++.h>
using namespace std;

/* macro helpers */
#define __NARGS(...) std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value
#define __DECOMPOSE_S(a, x) auto x = a;
#define __DECOMPOSE_N(a, ...) auto [__VA_ARGS__] = a;
constexpr void __() {}
#define __AS_PROCEDURE(...) __(); __VA_ARGS__; __()
#define __as_typeof(container) remove_reference<decltype(container)>::type
template <typename T> struct argument_type;
template <typename T, typename U> struct argument_type<T(U)> { using type = U; };

/* type aliases */
#if LONG_LONG_MAX != INT64_MAX
using ll = int64_t;
using ull = uint64_t;
#else
using ll = long long;
using ull = unsigned long long;
#endif
using int128 = __int128_t;
using uint128 = __uint128_t;
using ld = long double;
using pii = pair<int, int>;           using pil = pair<int, ll>;           using pid = pair<int, ld>;
using pli = pair<ll, int>;            using pll = pair<ll, ll>;            using pld = pair<ll, ld>;
using pdi = pair<ld, int>;            using pdl = pair<ld, ll>;            using pdd = pair<ld, ld>;
using tiii = tuple<int, int, int>;    using tiil = tuple<int, int, ll>;    using tiid = tuple<int, int, ld>;
using tili = tuple<int, ll, int>;     using till = tuple<int, ll, ll>;     using tild = tuple<int, ll, ld>;
using tidi = tuple<int, ld, int>;     using tidl = tuple<int, ld, ll>;     using tidd = tuple<int, ld, ld>;
using tlii = tuple<ll, int, int>;     using tlil = tuple<ll, int, ll>;     using tlid = tuple<ll, int, ld>;
using tlli = tuple<ll, ll, int>;      using tlll = tuple<ll, ll, ll>;      using tlld = tuple<ll, ll, ld>;
using tldi = tuple<ll, ld, int>;      using tldl = tuple<ll, ld, ll>;      using tldd = tuple<ll, ld, ld>;
using tdii = tuple<ld, int, int>;     using tdil = tuple<ld, int, ll>;     using tdid = tuple<ld, int, ld>;
using tdli = tuple<ld, ll, int>;      using tdll = tuple<ld, ll, ll>;      using tdld = tuple<ld, ll, ld>;
using tddi = tuple<ld, ld, int>;      using tddl = tuple<ld, ld, ll>;      using tddd = tuple<ld, ld, ld>;
template <typename T> using max_heap = priority_queue<T>;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<>>;
template <typename T> using oi = ostream_iterator<T>;
template <typename T> using ii = istream_iterator<T>;

/* constants */
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
constexpr ll MDL = 1e9 + 7;
constexpr ll PRIME = 998'244'353;
constexpr ll MDL1 = 8784491;
constexpr ll MDL2 = PRIME;
constexpr int128 INT128_MAX = numeric_limits<int128>::max();
constexpr uint128 UINT128_MAX = numeric_limits<uint128>::max();
constexpr int128 INT128_MIN = numeric_limits<int128>::min();
constexpr uint128 UINT128_MIN = numeric_limits<uint128>::min();

/* random */

mt19937_64 rd(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());

/* bit-wise operations */
#define lowbit(x) ((x) & -(x))
#define popcount(x) (__builtin_popcountll(ll(x)))
#define parity(x) (__builtin_parityll(ll(x)))
#define msp(x) (63LL - __builtin_clzll(ll(x)))
#define lsp(x) (__builtin_ctzll(ll(x)))

/* arithmetic operations */
#define mod(x, y) ((((x) % (y)) + (y)) % (y))

/* fast pairs */
#define upair ull
#define umake(x, y) (ull(x) << 32 | (ull(y) & ((1ULL << 32) - 1)))
#define u1(p) ((p) >> 32)
#define u2(p) ((p) & ((1ULL << 32) - 1))
#define ult std::less<upair>
#define ugt std::greater<upair>

#define ipair ull
#define imake(x, y) (umake(x, y))
#define i1(p) (int(u1(ll(p))))
#define i2(p) (ll(u2(p) << 32) >> 32)
struct ilt {
    bool operator()(const ipair& a, const ipair& b) const {
        if (i1(a) == i1(b)) return i2(a) < i2(b);
        else return i1(a) < i1(b);
    }
};
struct igt {
    bool operator()(const ipair& a, const ipair& b) const {
        if (i1(a) == i1(b)) return i2(a) > i2(b);
        else return i1(a) > i1(b);
    }
};

/* conditions */
#define loop while (1)
#define if_or(var, val) if (!(var == val)) var = val; else
#define continue_or(var, val) __AS_PROCEDURE(if (var == val) continue; var = val;)
#define break_or(var, val) __AS_PROCEDURE(if (var == val) break; var = val;)

/* hash */
struct safe_hash {
    // https://codeforces.com/blog/entry/62393
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct pair_hash {
    template <typename T, typename U>
    size_t operator()(const pair<T, U>& a) const {
        auto hash1 = safe_hash()(a.first);
        auto hash2 = safe_hash()(a.second);
        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }
        return hash1;
    }
};

uniform_int_distribution<mt19937::result_type> dist(PRIME);
const size_t __array_hash_b = 31, __array_hash_mdl1 = dist(rd), __array_hash_mdl2 = dist(rd);
struct array_hash {
    template <typename Sequence>
    size_t operator()(const Sequence& arr) const {
        size_t pw1 = 1, pw2 = 1;
        size_t res1 = 0, res2 = 0;
        for (auto&& x : arr) {
            res1 = (res1 + x * pw1) % __array_hash_mdl1;
            res2 = (res2 + x * pw2) % __array_hash_mdl2;
            pw1 = (pw1 * __array_hash_b) % __array_hash_mdl1;
            pw2 = (pw2 * __array_hash_b) % __array_hash_mdl2;
        }
        return res1 + res2;
    }
};

/* build data structures */
#define faster(um) __AS_PROCEDURE((um).reserve(1024); (um).max_load_factor(0.25);)
#define unordered_counter(from, to) __AS_PROCEDURE(unordered_map<__as_typeof(from), size_t, safe_hash> to; for (auto&& x : from) ++to[x];)
#define counter(from, to, cmp) __AS_PROCEDURE(map<__as_typeof(from), size_t, cmp> to; for (auto&& x : from) ++to[x];)
#define adj(ch, n) __AS_PROCEDURE(vector<vector<int>> ch((n) + 1);)
#define edge(ch, u, v) __AS_PROCEDURE(ch[u].push_back(v), ch[v].push_back(u);)
#define edgew(ch, u, v, ...) __AS_PROCEDURE(ch[u].emplace_back(v, __VA_ARGS__), ch[v].emplace_back(u, __VA_ARGS__);)
#define Edge(ch, u, v) __AS_PROCEDURE(ch[u].push_back(v);)
#define Edgew(ch, u, v, ...) __AS_PROCEDURE(ch[u].emplace_back(v, __VA_ARGS__);)
template <typename T, typename Iterator> pair<size_t, map<T, size_t>> discretize(Iterator __first, Iterator __last) {
    set<T> st(__first, __last);
    size_t N = 0;
    map<T, size_t> mp;
    for (auto&& x : st) mp[x] = ++N;
    return {N, mp};
}
template <typename T, typename Iterator> pair<size_t, unordered_map<T, size_t, safe_hash>> unordered_discretize(Iterator __first, Iterator __last) {
    set<T> st(__first, __last);
    size_t N = 0;
    unordered_map<T, size_t, safe_hash> mp;
    for (auto&& x : st) mp[x] = ++N;
    return {N, mp};
}

/* io */
#define untie __AS_PROCEDURE(ios_base::sync_with_stdio(0), cin.tie(NULL))

// add declarations to avoid cyclic dependency
template<typename T, typename U> istream& operator>>(istream&, pair<T, U>&);
template<typename T, typename U> ostream& operator<<(ostream&, const pair<T, U>&);
template<typename T, size_t N> istream& operator>>(istream&, array<T, N>&);
template <typename T, size_t N> ostream& operator<<(ostream&, const array<T, N>&);
template<typename Char, typename Traits, typename... Args>
decltype(auto) operator<<(std::basic_ostream<Char, Traits>&, const std::tuple<Args...>&);
template<typename T> ostream& operator<<(ostream&, const vector<T>&);
std::ostream& operator<<(std::ostream&, const int128&);

template<typename T, typename U> istream& operator>>(istream& in, pair<T, U>& p) {
    return in >> p.first >> p.second;
}
template<typename T, typename U> ostream& operator<<(ostream& out, const pair<T, U>& p) {
    out << "{" << p.first << ", " << p.second << "}";
    return out;
}
template<typename T, size_t N> istream& operator>>(istream& in, array<T, N>& a) {
    for (size_t i = 0; i < N; ++i) in >> a[i];
    return in;
}
template <typename T, size_t N> ostream& operator<<(ostream& out, const array<T, N>& a) {
    for (auto&& i : a) out << i << ' ';
    return out;
}
template<typename Char, typename Traits, typename Tuple, std::size_t... Index>
void print_tuple_impl(std::basic_ostream<Char, Traits>& os, const Tuple& t, std::index_sequence<Index...>) {
    using swallow = int[]; // guaranties left to right order
    (void)swallow { 0, (void(os << (Index == 0 ? "" : ", ") << std::get<Index>(t)), 0)... };
}
template<typename Char, typename Traits, typename... Args>
decltype(auto) operator<<(std::basic_ostream<Char, Traits>& os, const std::tuple<Args...>& t) {
    os << "{";
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << "}";
}
template<typename T> ostream& operator<<(ostream& out, const vector<T>& vec) {
    for (auto&& i : vec) out << i << ' ';
    return out;
}
std::ostream& operator<<(std::ostream& dest, const int128& value) {
    // https://stackoverflow.com/a/25115163/23881100
    std::ostream::sentry s( dest );
    if ( s ) {
        uint128 tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}
template<typename T> void __read(T& x) { cin >> x; }
template<typename T, typename... U> void __read(T& x, U&... args) { cin >> x; __read(args...); }
#define read(t, ...) __AS_PROCEDURE(argument_type<void(t)>::type __VA_ARGS__; __read(__VA_ARGS__);)
#define readvec(t, a, n) __AS_PROCEDURE(vector<argument_type<void(t)>::type> a(n); for (auto& x : a) cin >> x;)
#define readvec1(t, a, n) __AS_PROCEDURE(vector<argument_type<void(t)>::type> a((n) + 1); copy_n(ii<argument_type<void(t)>::type>(cin), (n), a.begin() + 1);)
#define putvec(a) __AS_PROCEDURE(copy(a.begin(), a.end(), oi<__as_typeof(a)::value_type>(cout, " ")); cout << endl;)
#define putvec1(a) __AS_PROCEDURE(copy(a.begin() + 1, a.end(), oi<__as_typeof(a)::value_type>(cout, " ")); cout << endl;)
#define putvec_eol(a) __AS_PROCEDURE(copy(a.begin(), a.end(), oi<__as_typeof(a)::value_type>(cout, "\n"));)
#define putvec1_eol(a) __AS_PROCEDURE(copy(a.begin() + 1, a.end(), oi<__as_typeof(a)::value_type>(cout, "\n"));)
#define debug(x) __AS_PROCEDURE(cerr << #x" = " << (x) << endl;)
#define debugvec(a) __AS_PROCEDURE(cerr << #a" = "; for (auto&& x : a) cerr << x << ' '; cerr << endl;)
#define deb(...) debug(make_tuple(__VA_ARGS__))

/* pops */
template <typename Container>
inline auto poptop(Container& q) {
    auto ret = q.top();
    q.pop();
    return ret;
}
template <typename Container>
inline auto popback(Container& q) {
    auto ret = q.back();
    q.pop_back();
    return ret;
}
template <typename Container>
inline auto popfront(Container& q) {
    auto ret = q.front();
    q.pop_front();
    return ret;
}

/* math */
template <typename return_t>
return_t qpow(ll b, ll p) {
    if (b == 0 and p != 0) return 0;
    if (p == 0) return 1;
    return_t half = qpow<return_t>(b, p / 2);
    if (p % 2 == 1) return half * half * b;
    else return half * half;
}

// dynamic modulus
ll qpow(ll b, ll p, ll mod) {
    if (b == 0 and p != 0) return 0;
    if (p == 0) return 1;
    ll half = qpow(b, p / 2, mod);
    if (p % 2 == 1) return (int128(half) * half % mod) * b % mod;
    else return half * half % mod;
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
// Accurately find `i` 'th root of `n` (taking the floor)
inline ll root(ll n, ll i) {
    ll l = 0, r = pow(LLONG_MAX, ld(1) / i);
    while (l < r) {
        ll mid = l + r + 1 >> 1;
        if (qpow<int128>(mid, i) <= n) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}
#pragma GCC diagnostic pop


#define comb(n, k) ((n) < 0 or (k) < 0 or (n) < (k) ? 0 : fact[n] / fact[k] / fact[(n) - (k)])
#define fastcomb(n, k) ((n) < 0 or (k) < 0 or (n) < (k) ? 0 : fact[n] * factrev[k] * factrev[(n) - (k)])

__attribute__((target("lzcnt")))
constexpr inline int lg2(ll x) { return x == 0 ? -1 : sizeof(ll) * 8 - 1 - __builtin_clzll(x); }

template <typename T>
T mygcd(T a, T b) { return b == 0 ? a : mygcd(b, a % b); }

void __exgcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) {
    x = 1, y = 0;
    return;
  }
  __exgcd(b, a % b, y, x);
  y -= a / b * x;
}

ll inverse(ll a, ll b) {
    ll x, y;
    __exgcd(a, b, x, y);
    return mod(x, b);
}

vector<tuple<int, int, ll>> decompose(ll x) {
    // return (factor, count, factor ** count)
    vector<tuple<int, int, ll>> res;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            int cnt = 0;
            ll pw = 1;
            while (x % i == 0) ++cnt, x /= i, pw *= i;
            res.emplace_back(i, cnt, pw);
        }
    }
    if (x != 1) {
        res.emplace_back(x, 1, x);
    }
    return res;
}

vector<pii> decompose_prime(int N) {
    // return (factor, count)
    vector<pii> result;
    for (int i = 2; i * i <= N; i++) {
        if (N % i == 0) {
            int cnt = 0;
            while (N % i == 0) N /= i, ++cnt;
            result.emplace_back(i, cnt);
        }
    }
    if (N != 1) {
        result.emplace_back(N, 1);
    }
    return result;
}

/* string algorithms */
vector<int> calc_next(string t) {  // pi function of t
    int n = (int)t.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && t[i] != t[j]) j = pi[j - 1];
        if (t[i] == t[j]) j++;
        pi[i] = j;
    }
    return pi;
}
vector<int> calc_z(string t) {  // z function of t
    int m = t.length();
    vector<int> z;
    z.push_back(m);
    pair<int, int> prev = {1, -1};
    for (int i = 1; i < m; ++i) {
        if (z[i - prev.first] + i <= prev.second) {
            z.push_back(z[i - prev.first]);
        } else {
            int j = max(i, prev.second + 1);
            while (j < m && t[j] == t[j - i]) ++j;
            z.push_back(j - i);
            prev = {i, j - 1};
        }
    }
    return z;
}
vector<int> kmp(string s, string t) {  // find all t in s
    string cur = t + '#' + s;
    int sz1 = s.size(), sz2 = t.size();
    vector<int> v;
    vector<int> lps = calc_next(cur);
    for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
        if (lps[i] == sz2) v.push_back(i - 2 * sz2);
    }
    return v;
}
int period(string s) {  // find the length of shortest recurring period
    int n = s.length();
    auto z = calc_z(s);
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0 && z[i] == n - i) {
            return i;
        }
    }
    return n;
}

/* modular arithmetic */
template <ll mdl> struct MLL {
    ll val;
    MLL(ll v = 0) : val(mod(v, mdl)) {}
    MLL(const MLL<mdl>& other) : val(other.val) {}
    friend MLL operator+(const MLL& lhs, const MLL& rhs) { return mod(lhs.val + rhs.val, mdl); }
    friend MLL operator-(const MLL& lhs, const MLL& rhs) { return mod(lhs.val - rhs.val, mdl); }
    friend MLL operator*(const MLL& lhs, const MLL& rhs) { return mod(lhs.val * rhs.val, mdl); }
    friend MLL operator/(const MLL& lhs, const MLL& rhs) { return mod(lhs.val * mod(inverse(rhs.val, mdl), mdl), mdl); }
    friend MLL operator%(const MLL& lhs, const MLL& rhs) { return mod(lhs.val - (lhs / rhs).val, mdl); }
    friend bool operator==(const MLL& lhs, const MLL& rhs) { return lhs.val == rhs.val; }
    friend bool operator!=(const MLL& lhs, const MLL& rhs) { return lhs.val != rhs.val; }
    MLL& operator+=(const MLL& rhs) { return *this = *this + rhs; }
    MLL& operator-=(const MLL& rhs) { return *this = *this - rhs; }
    MLL& operator*=(const MLL& rhs) { return *this = *this * rhs; }
    MLL& operator/=(const MLL& rhs) { return *this = *this / rhs; }
    MLL& operator%=(const MLL& rhs) { return *this = *this % rhs; }
};

template <ll mdl>
ostream& operator<<(ostream& out, const MLL<mdl>& num) {
    return out << num.val;
}

template <ll mdl>
istream& operator>>(istream& in, MLL<mdl>& num) {
    return in >> num.val;
}

// miscancellous
template <typename T, typename U>
bool chmax(T& lhs, const U& rhs) {
    bool ret = lhs < rhs;
    if (ret) {
        lhs = rhs;
    }
    return ret;
}
template <typename T, typename U>
bool chmin(T& lhs, const U& rhs) {
    bool ret = lhs > rhs;
    if (ret) {
        lhs = rhs;
    }
    return ret;
}

#define functor(func) ([&](auto&&... val) \
noexcept(noexcept(func(std::forward<decltype(val)>(val)...))) -> decltype(auto) \
{return func(std::forward<decltype(val)>(val)...);})
#define expr(ret, ...) ([&] (__VA_ARGS__) { return (ret); })
template <typename Func, typename RandomIt> void sort_by_key(RandomIt first, RandomIt last, Func extractor) {
    std::sort(first, last, [&] (auto&& a, auto&& b) { return std::less<>()(extractor(a), extractor(b)); });
}
template <typename Func, typename RandomIt, typename Compare> void sort_by_key(RandomIt first, RandomIt last, Func extractor, Compare comp) {
    std::sort(first, last, [&] (auto&& a, auto&& b) { return comp(extractor(a), extractor(b)); });
}
template <typename T, typename U, typename Iterator_T, typename Iterator_U>
vector<pair<T, U>> zip(Iterator_T a_first, Iterator_T a_last, Iterator_U b_first, Iterator_U b_last) {
    vector<pair<T, U>> res;
    auto a_it = a_first;
    auto b_it = b_first;
    for (; not (a_it == a_last) and not (b_it == b_last); ++a_it, ++b_it) {
        res.emplace_back(*a_it, *b_it);
    }
    return res;
}
template <typename T, typename U, typename Iterator_T, typename Iterator_U>
vector<pair<T, U>> zip_n(Iterator_T a_first, Iterator_U b_first, size_t n) {
    vector<pair<T, U>> res;
    if (n > 0) {
        res.emplace_back(*a_first, *b_first);
        for (size_t i = 1; i != n; ++i) {
            res.emplace_back(*++a_first, *++b_first);
        }
    }
    return res;
}
template <typename T>
class ArithmeticIterator : bidirectional_iterator_tag {
public:
    using difference_type = ptrdiff_t;
    using value_type = T;
private:
    value_type value;
public:
    ArithmeticIterator(const T& value) : value(value) {}
    value_type operator*() const { return value; }
    ArithmeticIterator<T>& operator++() { ++value; return *this; }
    ArithmeticIterator<T>& operator--() { --value; return *this; }
    bool operator==(const ArithmeticIterator<T>& rhs) const { return value == rhs.value; }
};
template <typename T> vector<pair<int, T>> enumerate(const vector<T>& container) {
    return zip<int, T>(ArithmeticIterator<int>(0), ArithmeticIterator<int>(INT_MAX), container.begin(), container.end());
}
#define initarray(init, N) (__initarray<decay<decltype(init)>::type, (N)>(init))
namespace detail {
    template <typename T, std::size_t...Is>
    constexpr std::array<T, sizeof...(Is)>
    make_array(const T& value, std::index_sequence<Is...>) {
        return {{(static_cast<void>(Is), value)...}};
    }
}

template <typename T, std::size_t N>
constexpr std::array<T, N> __initarray(const T& value) {
    return detail::make_array(value, std::make_index_sequence<N>());
}
/*******************************************************/

// #define SINGLE_TEST_CASE
// #define DUMP_TEST_CASE 7219
// #define TOT_TEST_CASE 10000

void dump() {}

void dump_ignore() {}

void prep() {
}

// __attribute__((target("popcnt")))
void solve() {
}

int main() {
#if __cplusplus < 201402L or defined(_MSC_VER) and not defined(__clang__)
    static_assert(false, "incompatible compiler variant detected.");
#endif
    untie;
    prep();
#ifdef SINGLE_TEST_CASE
    solve();
#else
    read(int, t);
    for (int i = 0; i < t; ++i) {
#ifdef DUMP_TEST_CASE
        if (t != (TOT_TEST_CASE)) {
            solve();
        } else if (i + 1 == (DUMP_TEST_CASE)) {
            dump();
        } else {
            dump_ignore();
        }
#else
        solve();
#endif
    }
#endif
}

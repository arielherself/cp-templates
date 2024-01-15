#include<bits/stdc++.h>
using namespace std;

#define __NARGS(...) std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value
#define __decompose_s(a, x) auto x = a;
#define __decompose_n(a, ...) auto [__VA_ARGS__] = a;

using ll = int64_t;
using ull = uint64_t;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define lowbit(x) ((x) & -(x))
#define popcount(x) (__builtin_popcountll(ll(x)))
#define parity(x) (__builtin_parityll(ll(x)))
#define msp(x) (63LL - __builtin_clzll(ll(x)))
#define lsp(x) (__builtin_ctzll(ll(x)))

#define upair ull
#define umake(x, y) (ull(x) << 32 | ull(y))
#define u1(p) ((p) >> 32)
#define u2(p) ((p) & ((1ULL << 32) - 1))
#define ult std::less<upair>
#define ugt std::greater<upair>

#define ipair ull
#define imake(x, y) (umake(x, y))
#define i1(p) (int(u1(p)))
#define i2(p) (int(u2(p)))
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

#define untie ios_base::sync_with_stdio(0), cin.tie(NULL)
template<typename T> void __read(T& x) { cin >> x; }
template<typename T, typename... U> void __read(T& x, U&... args) { cin >> x; __read(args...); }
#define read(type, ...) type __VA_ARGS__; __read(__VA_ARGS__);
#define readvec(type, a, n) vector<type> a(n); for (int i = 0; i < (n); ++i) cin >> a[i];
#define putvec(a) for (auto&& x : a) cout << x << ' '; cout << endl;
#define debug(x) cerr << #x" = " << x << endl;
#define debugvec(a) cerr << #a" = "; for (auto&& x : a) cerr << x << ' '; cerr << endl;

#define pa(a) __typeof(a) pa; pa.push_back({}); for (auto&&x : a) pa.push_back(pa.back() + x);
#define sa(a) __typeof(a) sa(a.size() + 1); {int n = a.size(); for (int i = n - 1; i >= 0; --i) sa[i] = sa[i + 1] + a[i];};

#define poptop(q, ...) auto [__VA_ARGS__] = q.top(); q.pop();
#define popback(q, ...) auto [__VA_ARGS__] = q.back(); q.pop_back();
#define popfront(q, ...) auto [__VA_ARGS__] = q.front();q.pop_front();

#define adj(ch, n) vector<vector<int>> ch(n);
#define edge(ch, u, v) ch[u].push_back(v), ch[v].push_back(u);
#define Edge(ch, u, v) ch[u].push_back(v);

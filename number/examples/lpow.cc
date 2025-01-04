constexpr int B = 2;
constexpr int N = 1e5;
constexpr int s = 31623;  // sqrt(MDL)
int a[N], b[N];

void prep() {
    a[0] = b[0] = 1;
    for(int i = 1; i <= s; i++) a[i] = (ll)a[i - 1] * B % MDL ;
    for(int i = 1; i <= s; i++) b[i] = (ll)b[i - 1] * a[s] % MDL ;
}

ll lpow(ll power) { return ll(b[power / s]) * a[power % s] % MDL; }


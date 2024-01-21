#include "../include.hh"

constexpr int N = 1e6 + 10;

char s[N];
int n, sa[N], rk[N], oldrk[N << 1], id[N], key1[N], cnt[N], height[N];

bool cmp(int x, int y, int w) {
  return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

void calc_sa() {
    n = strlen(s + 1);
    int i, m = 127, p, w;
    for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
      for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
      for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

      for (w = 1;; w <<= 1, m = p) {
        for (p = 0, i = n; i > n - w; --i) id[++p] = i;
        for (i = 1; i <= n; ++i)
          if (sa[i] > w) id[++p] = sa[i] - w;

        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i) ++cnt[key1[i] = rk[id[i]]];

        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[key1[i]]--] = id[i];
        memcpy(oldrk + 1, rk + 1, n * sizeof(int));
        for (p = 0, i = 1; i <= n; ++i)
          rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
        if (p == n) {
          break;
        }
      }
}

void calc_height() {
  for (i = 1, k = 0; i <= n; ++i) {
    if (rk[i] == 0) continue;
    if (k) --k;
    while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
    height[rk[i]] = k;
  }
}

int main() {
    untie;
    cin >> (s + 1);  // array s starts from index 1
    calc_sa();
    for (int i = 1; i <= n; ++i) cout << sa[i] << " \n"[i == n];
}

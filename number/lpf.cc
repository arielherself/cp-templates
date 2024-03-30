constexpr int N = 1e7 + 10;

int lpf[N];

void era(int n) {
    lpf[0] = lpf[1] = -1;
    for (int i = 2; i <= n; ++i) lpf[i] = i;
    for (int i = 2; i <= n; ++i) {
        if (lpf[i] == i) {
            if ((ll)i * i > n) continue;
            for (int j = i * i; j <= n; j += i) {
                if (lpf[j] == j) {
                    lpf[j] = i;
                }
            }
        }
    }
}


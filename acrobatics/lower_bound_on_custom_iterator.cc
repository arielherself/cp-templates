#include <bits/stdc++.h>
using namespace std;

template <typename T> class Number {
    template <typename U> friend Number<U> &operator++(Number<U> &);

  public:
    using iterator_category = forward_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;
    Number(T a) : dat(a) {}
    bool operator==(const Number<T> &o) const { return dat == *o; }
    bool operator!=(const Number<T> &o) const { return dat != *o; }
    const T &operator*() const { return dat; }
    Number<T> operator+(ptrdiff_t dt) { return Number<T>(dat + dt); }

  private:
    T dat;
    void _plusplus() { ++dat; }
};

template <typename T> Number<T> &operator++(Number<T> &it) {
    it._plusplus();
    return it;
}

int main() {
    auto cmp = [](int a, int x) { return a <= x; };
    cout << *lower_bound(Number(1), Number(5), 3, cmp); // cout << 3 + 1;
    return 0;
}
